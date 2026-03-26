#include "./Shader.h"

#include <exception>

#include <utils/Log.h>
#include <utils/File.h>

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
void Shader::setUniform(const vec2& value, std::string name) const {
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}

template <>
void Shader::setUniform(const vec3& value, std::string name) const {
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}

template <>
void Shader::setUniform(const vec4& value, std::string name) const {
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}

template <>
void Shader::setUniform(const mat4& value, std::string name) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, false, value_ptr(value));
}

template <>
void Shader::setUniform(const Material& value, std::string name) const {
	setUniform(value.ambient, name + ".ambient");
    setUniform(value.diffuse, name + ".diffuse");
	setUniform(value.specular, name + ".specular");
	
	setUniform(value.color, name + ".color");
    
    if (value.useTexture) {
    	setUniform<GLuint>(0, name + ".diffuseTex");
	    setUniform<GLuint>(1, name + ".specularTex");
    }
	
    setUniform(value.useTexture, name + ".useTexture");
}

template <>
void Shader::setUniform(const Light& value, std::string name) const {
	setUniform<GLfloat>(value.intensity, name + ".intensity");

	setUniform<vec3>(value.position, name + ".position");
	setUniform<vec3>(value.color, name + ".color");

	setUniform<GLfloat>(value.constant, name + ".constant");
	setUniform<GLfloat>(value.linear, name + ".linear");
	setUniform<GLfloat>(value.quadratic, name + ".quadratic");
}

template <>
void Shader::setUniform(const Camera& value, std::string name) const {
	setUniform(value.viewMatrix, "viewMatrix");

	setUniform(value.position, name + ".position");
}

template <>
void Shader::setUniform(const ProjectionMatrix& value, std::string name) const {
	setUniform(value.projectionMatrix, name);
}

