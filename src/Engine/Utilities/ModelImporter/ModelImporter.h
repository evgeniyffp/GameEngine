// Engine/Utilities/ModelImporter/ModelImporter.h
#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Engine/Graphics/Mesh/Mesh.h>
#include <Engine/Graphics/Material/Material.h>
#include <Engine/Graphics/Texture/Texture.h>

#include <utils/Log.h>

struct LoadedModel {
    std::vector<Mesh> meshes;
    std::vector<Material> materials; // соответствие индексу меша (если у каждого меша свой материал)
};

class ModelImporter {
public:
    // Загрузить только меши (без материалов)
    static std::vector<Mesh> loadMeshes(const std::string& path, bool flipUVs = true) {
        Assimp::Importer importer;
        unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                             aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace;
        if (flipUVs)
            flags |= aiProcess_FlipUVs;

        const aiScene* scene = importer.ReadFile(path, flags);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            Log::error("ModelImporter::loadMeshes - Assimp error: {}", importer.GetErrorString());
            return {};
        }

        std::vector<Mesh> meshes;
        processNode(scene->mRootNode, scene, meshes);
        return meshes;
    }

    // Загрузить только материалы (без мешей)
    static std::vector<Material> loadMaterials(const std::string& path, bool flipUVs = true) {
        Assimp::Importer importer;
        unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                             aiProcess_JoinIdenticalVertices;
        if (flipUVs)
            flags |= aiProcess_FlipUVs;

        const aiScene* scene = importer.ReadFile(path, flags);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            Log::error("ModelImporter::loadMaterials - Assimp error: {}", importer.GetErrorString());
            return {};
        }

        std::vector<Material> materials;
        // Извлекаем все материалы из сцены (глобальный массив)
        if (scene->HasMaterials()) {
            std::string directory = std::filesystem::path(path).parent_path().string();
            for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
                materials.push_back(processMaterial(scene->mMaterials[i], directory));
            }
        }
        return materials;
    }

    // Загрузить всё: меши + материалы, автоматически связывая материалы с мешами
    static LoadedModel loadFull(const std::string& path, bool flipUVs = true) {
        Assimp::Importer importer;
        unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                             aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace;
        if (flipUVs)
            flags |= aiProcess_FlipUVs;

        const aiScene* scene = importer.ReadFile(path, flags);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            Log::error("ModelImporter::loadFull - Assimp error: {}", importer.GetErrorString());
            return {};
        }

        LoadedModel result;
        std::string directory = std::filesystem::path(path).parent_path().string();

        // Предварительно загружаем все материалы сцены
        std::vector<Material> sceneMaterials;
        if (scene->HasMaterials()) {
            for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
                sceneMaterials.push_back(processMaterial(scene->mMaterials[i], directory));
            }
        }

        // Рекурсивно обходим узлы и создаём меши, привязывая материал по индексу
        processNodeFull(scene->mRootNode, scene, result.meshes, result.materials, sceneMaterials);
        return result;
    }

private:
    // Вспомогательная: обход узлов (только меши, без материалов)
    static void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes) {
        for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            processNode(node->mChildren[i], scene, meshes);
        }
    }

    // Обход с заполнением мешей и материалов (каждый меш получает копию материала)
    static void processNodeFull(aiNode* node, const aiScene* scene,
                                std::vector<Mesh>& outMeshes,
                                std::vector<Material>& outMaterials,
                                const std::vector<Material>& sceneMaterials) {
        for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            outMeshes.push_back(processMesh(mesh, scene));
            // Привязываем материал, соответствующий индексу mesh->mMaterialIndex
            if (mesh->mMaterialIndex < sceneMaterials.size())
                outMaterials.push_back(sceneMaterials[mesh->mMaterialIndex]);
            else {
                // fallback материал
                outMaterials.emplace_back(glm::vec3(0.2f), glm::vec3(0.8f), glm::vec3(0.5f), glm::vec3(1.0f));
                Log::warning("ModelImporter: mesh has invalid material index {}, using default", mesh->mMaterialIndex);
            }
        }
        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            processNodeFull(node->mChildren[i], scene, outMeshes, outMaterials, sceneMaterials);
        }
    }

    // Конвертация aiMesh в Mesh (вершины + индексы)
    static Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;

        // Вершины
        vertices.reserve(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            Vertex vertex{};
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.normal   = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            vertex.color    = glm::vec3(1.0f); // default white, можно читать vertex colors при наличии

            // Текстурные координаты (берём первый слой)
            if (mesh->mTextureCoords[0]) {
                vertex.texcoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            } else {
                vertex.texcoord = glm::vec2(0.0f);
            }
            vertices.push_back(vertex);
        }

        // Индексы (из faces)
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(face.mIndices[j]);
            }
        }

        return Mesh(vertices, indices);
    }

    // Конвертация aiMaterial в Material движка
    static Material processMaterial(aiMaterial* mat, const std::string& directory) {
        aiColor3D ambient(0.2f, 0.2f, 0.2f);
        aiColor3D diffuse(0.8f, 0.8f, 0.8f);
        aiColor3D specular(0.5f, 0.5f, 0.5f);
        mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
        mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
        mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);

        Material material(glm::vec3(ambient.r, ambient.g, ambient.b),
                          glm::vec3(diffuse.r, diffuse.g, diffuse.b),
                          glm::vec3(specular.r, specular.g, specular.b));

        aiString path;
        // Загрузка diffuse текстуры
        if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
            std::string fullPath = directory + "/" + path.C_Str();
            try {
                auto diffuseTex = std::make_shared<Texture>(fullPath, TEXTURE_2D);
                material.setDiffuseTexture(diffuseTex);
            }   
            catch (const std::exception& e) {
                Log::error("ModelImporter: failed to load diffuse texture '{}': {}", fullPath, e.what());
            }
        }
        
        // Загрузка specular текстуры
        if (mat->GetTexture(aiTextureType_SPECULAR, 0, &path) == AI_SUCCESS) {
            std::string fullPath = directory + "/" + path.C_Str();
            try {
                auto specularTex = std::make_shared<Texture>(fullPath, TEXTURE_2D);
                material.setSpecularTexture(specularTex);
            }   
            catch (const std::exception& e) {
                Log::error("ModelImporter: failed to load specular texture '{}': {}", fullPath, e.what());
            }
        }

        return material;
    }
};
