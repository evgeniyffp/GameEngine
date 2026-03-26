#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <Engine/Graphics/Material/Material.h>
#include <Engine/Graphics/Light/Light.h>
#include <Engine/Camera/Camera.h>

#include <Engine/Utilities/Setting/Setting.h>
#include <Engine/Utilities/ProjectionMatrix/ProjectionMatrix.h>

constexpr auto Fragment_Shader = GL_FRAGMENT_SHADER;
constexpr auto Vertex_Shader = GL_VERTEX_SHADER;
constexpr auto Geometry_Shader = GL_GEOMETRY_SHADER;

class Shader {
private:
	GLuint id = 0;

	void createProgram();
	void deleteProgram();

public:
	Shader();
	Shader(std::string vertexShaderFileName, std::string fragmentShaderFileName);

	~Shader();

	GLuint getProgram();
	
    void use() const;
	void unUse() const;

	void addShader(GLenum typeShader, std::string fileName);

	void linkProgram();

    template <typename T>
    void setUniform(const T& value, std::string name) const;
    
    template <typename T>
    void setUniformArray(const std::vector<T>& vec, std::string name) const {
        setUniform(vec.size(), name + ".count");
    	for (int i = 0; i < vec.size(); ++i) {
            setUniform(vec[i], name + ".array[" + std::to_string(i) + "]");
	    }
    }
};

#include "./ShaderUser.h"

