#include "ObjLoader.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <fstream>
#include <sstream>

#include <map>
#include <algorithm>

#include <Engine/Graphics/Vertex/Vertex.h>

#include <utils/Log.h>

std::map<std::string, std::vector<Vertex>> arrayOfVertex;

std::string ObjectLoader::compile(std::string fileName) {
	std::ifstream in_file;

	std::string file;
	std::string line;

	std::stringstream ss;
	std::string prefix;

	in_file.open(fileName);
	
    std::string info = "ObjLoader.cpp => ObjectLoader::compile() => file \"" + fileName + "\" open";

	if (!in_file.is_open()) {
        Log::error(info);
		throw info;
	}
    Log::debug(info);

	while (std::getline(in_file, line)) {
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
				continue;
		else if (prefix == "f") {
            line = "";
            std::vector<std::string> indices;
            std::string vertex;
            while (ss >> vertex) 
                indices.push_back(vertex);

            if (indices.size() >= 3) {
                std::string base = indices[0];
                for (size_t i = 1; i < indices.size() - 1; ++i) {
                    line += "f " + base + " " + indices[i] + " " + indices[i + 1] + "\n";
                    line += "f " + indices[i + 1] + " " + indices[i] + " " + base + "\n";
                }
            }
            else {
                Log::warning("ObjLoader.cpp => ObjectLoader::compile() >= count of `\\` must be more or equal that 3 (aka " + line + ")");
            }
		}

		file += line + "\n";
	}
	
	in_file.close();
    Log::debug("ObjLoader.cpp => ObjectLoader::compile() => file \"" + fileName + "\" compiled succesfull");

	return file;
}

std::vector<Vertex> ObjectLoader::get(std::string fileName)
{
	if (arrayOfVertex.find(fileName) == arrayOfVertex.cend())
	{
		std::vector <vec3> vertex_positions;
		std::vector <vec2> vertex_texcoords;
		std::vector <vec3> vertex_normals;

		std::vector <size_t> vertex_position_indicies;
		std::vector <size_t> vertex_texcoord_indicies;
		std::vector <size_t> vertex_normal_indicies;

		std::vector <Vertex> vertices;

		std::stringstream file;
		file.str(ObjectLoader::compile(fileName));

		std::stringstream ss;
		std::string line = "";

		std::string prefix;

		vec3 temp_vec3;
		vec2 temp_vec2;
		size_t temp_size_t;

		std::string info = "ObjLoader.cpp => loadObj() => file open";

        Log::debug(info);
		while (std::getline(file, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "v")
			{
				ss >> temp_vec3.x;
				ss >> temp_vec3.y;
				ss >> temp_vec3.z;
				vertex_positions.push_back(temp_vec3);
			}
			else if (prefix == "vt")
			{
				ss >> temp_vec2.x;
				ss >> temp_vec2.y;
				vertex_texcoords.push_back(temp_vec2);
			}
			else if (prefix == "vn")
			{
				ss >> temp_vec3.x;
				ss >> temp_vec3.y;
				ss >> temp_vec3.z;
				vertex_normals.push_back(temp_vec3);
			}
			else if (prefix == "f")
			{
				size_t counter = 0;
				while (ss >> temp_size_t)
				{
					if (counter == 0)
						vertex_position_indicies.push_back(temp_size_t);
					else if (counter == 1)
						vertex_texcoord_indicies.push_back(temp_size_t);
					else if (counter == 2)
						vertex_normal_indicies.push_back(temp_size_t);

					if (ss.peek() == '/')
					{
						++counter;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' ')
					{
						++counter;
						ss.ignore(1, ' ');
					}

					if (counter > 2) counter = 0;
				}
			}
      else if (prefix == "o") {
        std::string object_name;
        ss >> object_name;

      // TODO:
      }
        else if (prefix == "g") {
            // skip
        }
      else if (prefix == "s") {
        std::string str;
        ss >> str;
      }
      else if (prefix == "usemtl") {
        std::string mtl_name;
        ss >> mtl_name;
      }
			else
			{
                Log::warning("ObjLoader.cpp => loadObj() => unknown prefix in obj file \'" + prefix + "\'");
			}
		}
		vertices.resize(vertex_position_indicies.size(), Vertex());
		for (size_t i = 0; i < vertices.size(); ++i)
		{
			vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
			vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
			vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];

			vertices[i].color = vec3(0.5f);
		}

        Log::debug("ObjLoader.cpp => loadObj() => get " + std::to_string(vertices.size()) + " vertices");

		arrayOfVertex[fileName] = vertices;
	}

	return arrayOfVertex[fileName];
}

