#include "Mesh.h"

#include <utils/displayInfo.h>

void Mesh::initVAO() {
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
    
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
    glBufferData(GL_ARRAY_BUFFER,
		vertexArray.size() * sizeof(Vertex), vertexArray.data(),
		GL_STATIC_DRAW);

	if (countIndices != 0) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			countIndices * sizeof(GLuint), indexArray,
			GL_STATIC_DRAW);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

void Mesh::uniformsUpdate(const Shader& shader) const {
	shader.setUniform_mat4f(modelMatrix, "modelMatrix");
}

// be carefull with args (starts with _) and don't confuse them with the variables in the class itself
Mesh::Mesh(
	std::vector<Vertex> _vertexArray,
	GLuint* _indexArray, const GLuint& _countIndices, 
	vec3 _position, vec3 _origin, vec3 _rotation, vec3 _scale
)       : vertexArray(std::move(_vertexArray)), position(_position), origin(_origin), rotation(_rotation), scale(_scale)
        ,  countIndices(_countIndices) {
	indexArray = new GLuint[countIndices];
	for (GLuint i = 0; i < countIndices; ++i)
		indexArray[i] = _indexArray[i];

	initVAO();
	update();
}

/*
Mesh::Mesh(
	Primitiv* primitive,
	vec3 position,
	vec3 origin, 
	vec3 rotation,
	vec3 scale)
    : Mesh(
        primitive->vertices,
	    primitive->indices.data(), (GLuint)primitive->indices.size(),
	    position, origin, rotation, scale
    )
{}
*/

Mesh::Mesh(const Mesh& object) : Mesh(
	object.vertexArray,
	object.indexArray, object.countIndices,
	object.position, object.origin, object.rotation, object.scale
) {}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	if (countIndices != 0)
		glDeleteBuffers(1, &EBO);

	delete[] indexArray;
}

vec3 Mesh::getPosition() const {
    return position;
}
void Mesh::setPosition(const vec3& new_position)  { 
    position = new_position;
}
void Mesh::move(const vec3& delta_position)  { 
    position += delta_position;
}

vec3 Mesh::getRotation() const  {
    return rotation;
}
void Mesh::setRotation(const vec3& new_rotation)  {
    rotation = new_rotation;
}
void Mesh::rotate(const vec3& delta_rotation)  {
    rotation += delta_rotation;
}

vec3 Mesh::getScale() const {
    return scale;
}
void Mesh::setScale(const vec3& new_scale) {
    scale = new_scale;
}

void Mesh::setOrigin(vec3 new_origin) { 
    origin = new_origin;
}

void Mesh::update() {
	modelMatrix = mat4(1.0f);
	modelMatrix = translate(modelMatrix, origin);
	modelMatrix = glm::rotate(modelMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = translate(modelMatrix, position - origin);
	modelMatrix = glm::scale(modelMatrix, scale);
}

void Mesh::render(const Shader& shader) const {
	uniformsUpdate(shader);

	shader.use();

	glBindVertexArray(VAO);
	if (countIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, vertexArray.size());
	else
		glDrawElements(GL_TRIANGLES, countIndices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	shader.unUse();

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

