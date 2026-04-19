#include "./Shader.h"

#include <exception>

#include <utils/Log.h>
#include <utils/File.h>

#include <Engine/ECS/Components/CameraComponent.h>
#include <Engine/ECS/Components/LightComponent.h>
#include <Engine/ECS/Components/TransformComponent.h>

#include <Engine/Graphics/Material/Material.h>

#include <Engine/Utilities/Setting/Setting.h>
#include <Engine/Utilities/ProjectionMatrix/ProjectionMatrix.h>

void Shader::createProgram() { 
    id = glCreateProgram();
}

void Shader::deleteProgram() {
    glDeleteProgram(id);
}

Shader::Shader() {
    createProgram();
}

Shader::Shader(std::string vertexShaderFileName, std::string fragmentShaderFileName)
        : Shader() {
	addShader(Vertex_Shader, vertexShaderFileName);
	addShader(Fragment_Shader, fragmentShaderFileName);

	linkProgram();
}

Shader::~Shader() { 
    deleteProgram(); 
}

GLuint Shader::getProgram() { 
    return id; 
}

void Shader::use() const {
    glUseProgram(id); 
}

void Shader::unUse() const { 
    glUseProgram(0); 
}

void Shader::addShader(GLenum typeShader, std::string fileName) {
	char infoLog[512];
	GLint succes;

	GLuint shader = glCreateShader(typeShader);
	
    std::string strSourceCode = readFile(fileName);
	
    const GLchar* sourceNode = strSourceCode.c_str();
	glShaderSource(shader, 1, &sourceNode, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
	
    std::string info = "Shader.h => Shader::addShader() => shader compile";
	
    if (!succes) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
        Log::error(infoLog);
		throw info;
	}
    Log::debug(info);

	glAttachShader(id, shader);
	
	glDeleteShader(shader);
}

void Shader::linkProgram() {
	char infoLog[512];
	GLint succes;

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &succes);
	
    std::string info = "Shader.h => Shader::addShaders() => program link";
	
    if (!succes) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
        Log::error(infoLog);
		throw info;
	}
    Log::debug(info);
}

template <>
void Shader::setUniform(const GLint& value, std::string name) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

template <>
void Shader::setUniform(const GLuint& value, std::string name) const {
	glUniform1ui(glGetUniformLocation(id, name.c_str()), value);
}

template <>
void Shader::setUniform(const size_t& value, std::string name) const {
    setUniform<GLuint>(static_cast<GLuint>(value), name);
}

template <>
void Shader::setUniform(const bool& value, std::string name) const {
    setUniform<GLint>(static_cast<GLint>(value), name);
}

template <>
void Shader::setUniform(const GLfloat& value, std::string name) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

template <>
void Shader::setUniform(const glm::vec2& value, std::string name) const {
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}

template <>
void Shader::setUniform(const glm::vec3& value, std::string name) const {
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}

template <>
void Shader::setUniform(const glm::vec4& value, std::string name) const {
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}

template <>
void Shader::setUniform(const glm::mat4& value, std::string name) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, false, value_ptr(value));
}

template <>
void Shader::setUniform(const Material& value, std::string name) const {
	setUniform(value.getAmbient(), name + ".ambient");
    setUniform(value.getDiffuse(), name + ".diffuse");
	setUniform(value.getSpecular(), name + ".specular");
	
	setUniform(value.getColor(), name + ".color");
    
    setUniform(value.isUseTexture(), name + ".useTexture");
    
    if (value.isUseTexture()) {
    	setUniform<GLuint>(0, name + ".diffuseTex");
	    setUniform<GLuint>(1, name + ".specularTex");
    }
}

template <>
void Shader::setUniform(const std::pair<TransformComponent, LightComponent>& value, std::string name) const {
	const auto& transform_component = value.first;
	const auto& light_component = value.second;

    setUniform<GLfloat>(light_component.intensity, name + ".intensity");

	setUniform<glm::vec3>(transform_component.position_component.position, name + ".position");
	setUniform<glm::vec3>(light_component.color, name + ".color");

	setUniform<GLfloat>(light_component.constant, name + ".constant");
	setUniform<GLfloat>(light_component.linear, name + ".linear");
	setUniform<GLfloat>(light_component.quadratic, name + ".quadratic");
}

template <>
void Shader::setUniform(const CameraComponent& value, std::string name) const {
	setUniform(value.viewMatrix, "viewMatrix");

	setUniform(value.position, name + ".position");
}

template <>
void Shader::setUniform(const ProjectionMatrix& value, std::string name) const {
	setUniform(value.get(), name);
}

