#include "./Shader.h"

#include <exception>

#include <utils/displayInfo.h>
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
	std::string version = std::to_string(GLSetting::Version::majorerVersion() * 100 + GLSetting::Version::minorVersion() * 10);
	strSourceCode.replace(strSourceCode.find("#version"), strSourceCode.find("\n"), "#version " + version);
	
    const GLchar* sourceNode = strSourceCode.c_str();
	glShaderSource(shader, 1, &sourceNode, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
	
    std::string info = "Shader.h => Shader::addShader() => shader compile";
	displayInfo(info);
	
    if (!succes) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		info += ":\n" + std::string(infoLog);
		throw info;
	}

	glAttachShader(id, shader);
	
	glDeleteShader(shader);
	unUse();
}

void Shader::linkProgram() {
	char infoLog[512];
	GLint succes;

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &succes);
	
    std::string info = "Shader.h => Shader::addShaders() => program link";
	displayInfo(info);
	
    if (!succes) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		info += ":\n" + std::string(infoLog);
		throw info;
	}

	unUse();
}

void Shader::setUniform_1i(GLint value, std::string name) const {
	use();
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	unUse();
}

void Shader::setUniform_1f(GLfloat value, std::string name) const {
	use();
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	unUse();
}

void Shader::setUniform_vec2f(vec2 value, std::string name) const {
	use();
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
	unUse();
}

void Shader::setUniform_vec3f(vec3 value, std::string name) const {
	use();
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
	unUse();
}

void Shader::setUniform_vec4f(vec4 value, std::string name) const {
	use();
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
	unUse();
}

void Shader::setUniform_mat4f(mat4 value, std::string name, GLboolean transpose) const {
	use();
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, transpose, value_ptr(value));
	unUse();
}

void Shader::setUniform_material(const Material& value, std::string name) const {
	setUniform_vec3f(value.ambient, name + ".ambient");
	setUniform_vec3f(value.diffuse, name + ".diffuse");
	setUniform_vec3f(value.specular, name + ".specular");

	setUniform_texture(0, name + ".diffuseTex");
	setUniform_texture(1, name + ".specularTex");

	setUniform_1i(value.useTexture, name + ".useTexture");
}

void Shader::setUniform_texture(GLint textureUnit, std::string name) const {
	setUniform_1i(textureUnit, name);
}

void Shader::setUniform_light(const Light& value, std::string name) const {
	setUniform_1f(value.intensity, name + ".intensity");

	setUniform_vec3f(value.position, name + ".position");
	setUniform_vec3f(value.color, name + ".color");

	setUniform_1f(value.constant, name + ".constant");
	setUniform_1f(value.linear, name + ".linear");
	setUniform_1f(value.quadratic, name + ".quadratic");
}

void Shader::setUniform_camera(const Camera& value, std::string name) const {
	setUniform_mat4f(value.viewMatrix, "viewMatrix");

	setUniform_vec3f(value.position, "cameraPosition");
}

void Shader::setUniformProjectionMatrix(const ProjectionMatrix& value, std::string name) const {
	setUniform_mat4f(value.projectionMatrix, name);
}

