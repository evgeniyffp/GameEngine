#pragma once

#include <vector>

#include <glad/glad.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
using namespace glm;

#include <Engine/Graphics/Vertex/Vertex.h>
#include <Engine/Graphics/Shader/Shader.h>
#include <Engine/Primitives/Primitives.h>

#include <Engine/Graphics/Transformable/Transformable.h>

class Mesh : public Transformable {
private:
    std::vector<Vertex> vertexArray;

    std::vector<GLuint> indexArray;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	vec3 position;
	vec3 origin;
	vec3 rotation;
	vec3 scale;
	mat4 modelMatrix;

	void initVAO();

	void uniformsUpdate(const Shader& shader) const;

public:
	Mesh(
		std::vector<Vertex> vertices,
		std::vector<GLuint> indices = {},
        vec3 position = vec3(0.0f), 
		vec3 origin = vec3(0.0f),
		vec3 rotation = vec3(0.0f), 
		vec3 scale = vec3(1.0f)
	);
/*
	Mesh(
		Primitiv* primitive,
		vec3 position = vec3(0.0f),
		vec3 origin = vec3(0.0f),
		vec3 rotation = vec3(0.0f), 
		vec3 scale = vec3(1.0f)
	);
*/	
	Mesh(const Mesh& object);

	~Mesh();
	
    vec3 getPosition() const override;
	void setPosition(const vec3& new_position) override;
	void move(const vec3& delta_position) override;

    vec3 getRotation() const override;
	void setRotation(const vec3& new_rotation) override;
	void rotate(const vec3& delta_rotation) override;

    vec3 getScale() const;
    void setScale(const vec3& new_scale);
	
	void setOrigin(vec3 origin);

    void update();

	void render(const Shader& shader) const;
};

