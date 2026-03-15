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
#include <Engine/Graphics/Camera/Camera.h>

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

	void setUniform_1i(GLint value, std::string name) const;
	void setUniform_1f(GLfloat value, std::string name) const;
	
	void setUniform_vec2f(vec2 value, std::string name) const;
	void setUniform_vec3f(vec3 value, std::string name) const;
	void setUniform_vec4f(vec4 value, std::string name) const;

	void setUniform_mat4f(mat4 value, std::string name, GLboolean transpose = GL_FALSE) const;

	void setUniform_material(const Material& value, std::string name) const;

	void setUniform_texture(GLint textureUnit, std::string name) const;

	void setUniform_light(const Light& value, std::string name) const;

	void setUniform_camera(const Camera& value, std::string name) const;

	void setUniformProjectionMatrix(const ProjectionMatrix& value, std::string name) const;
};

