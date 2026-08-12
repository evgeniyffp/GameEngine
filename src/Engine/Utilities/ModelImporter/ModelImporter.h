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

#include <Engine/ECS/Components/ModelComponent.h>

#include <utils/Log.h>

static glm::mat4 toGlmMat4(const aiMatrix4x4& aiMat) {
    glm::mat4 glmMat;
    glmMat[0][0] = aiMat.a1; glmMat[1][0] = aiMat.b1; glmMat[2][0] = aiMat.c1; glmMat[3][0] = aiMat.d1;
    glmMat[0][1] = aiMat.a2; glmMat[1][1] = aiMat.b2; glmMat[2][1] = aiMat.c2; glmMat[3][1] = aiMat.d2;
    glmMat[0][2] = aiMat.a3; glmMat[1][2] = aiMat.b3; glmMat[2][2] = aiMat.c3; glmMat[3][2] = aiMat.d3;
    glmMat[0][3] = aiMat.a4; glmMat[1][3] = aiMat.b4; glmMat[2][3] = aiMat.c4; glmMat[3][3] = aiMat.d4;
    return glmMat;
}

class ModelImporter {
public:
    // Загрузить всё: меши + материалы, автоматически связывая материалы с мешами
    static ModelComponent loadFull(const std::string& path, bool flipUVs = true) {
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
        
        std::vector<Mesh> outMeshes;
        std::vector<Material> outMaterials;
        std::vector<glm::mat4> outMatrices;
                           
        std::string directory = std::filesystem::path(path).parent_path().string();

        // Предварительно загружаем все материалы сцены
        std::vector<Material> sceneMaterials;
        if (scene->HasMaterials()) {
            for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
                sceneMaterials.push_back(processMaterial(scene->mMaterials[i], directory));
            }
        }

        // Рекурсивно обходим узлы и создаём меши, привязывая материал по индексу
        processNodeFull(scene->mRootNode, scene, outMeshes, outMaterials, outMatrices, sceneMaterials);

        ModelComponent model;

        model.parts.reserve(outMeshes.size());
        for (size_t i = 0; i < outMeshes.size(); ++i) {
            model.parts.push_back({ std::move(outMeshes[i]), std::move(outMaterials[i]), std::move(outMatrices[i]) });
        }

        return model;
    }

private:
    static void processNodeFull(aiNode* node, const aiScene* scene,
                            std::vector<Mesh>& outMeshes,
                            std::vector<Material>& outMaterials,
                            std::vector<glm::mat4>& outMatrices,  // новый вектор для матриц
                            const std::vector<Material>& sceneMaterials,
                            const glm::mat4& parentTransform = glm::mat4(1.0f)) {
        // Вычисляем локальную матрицу узла
        glm::mat4 nodeLocal = toGlmMat4(node->mTransformation);
        glm::mat4 accumulated = parentTransform * nodeLocal; // порядок важен: сначала локальная, потом родительская

        // Обрабатываем меши этого узла
        for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            outMeshes.push_back(processMesh(mesh));
            // Материал
            if (mesh->mMaterialIndex < sceneMaterials.size())
                outMaterials.push_back(sceneMaterials[mesh->mMaterialIndex]);
            else {
                outMaterials.emplace_back(glm::vec3(0.2f), glm::vec3(0.8f), glm::vec3(0.5f), glm::vec3(1.0f));
                Log::warning("ModelImporter: mesh has invalid material index {}, using default", mesh->mMaterialIndex);
            }
            // Сохраняем накопленную матрицу для этого меша
            outMatrices.push_back(accumulated);
        }

        // Рекурсивно обходим детей
        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            processNodeFull(node->mChildren[i], scene, outMeshes, outMaterials, outMatrices, sceneMaterials, accumulated);
        }
    }

    // Конвертация aiMesh в Mesh (вершины + индексы)
    static Mesh processMesh(aiMesh* mesh) {
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
