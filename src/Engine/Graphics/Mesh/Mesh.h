#pragma once

#include <vector>

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <Engine/Graphics/Vertex/Vertex.h>

class Mesh {
private:
    bool is_clear = false;
    std::vector<Vertex> vertexArray;

    std::vector<GLuint> indexArray;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	void init();

public:
	Mesh(
		std::vector<Vertex> vertices,
		std::vector<GLuint> indices = {}
	);

    Mesh(Mesh&& other) : vertexArray(std::move(other.vertexArray)), indexArray(std::move(other.indexArray)), VAO(other.VAO), VBO(other.VBO), EBO(other.EBO) {
        other.is_clear = true;
        other.VAO = other.VBO = other.EBO = 0;
    }

	~Mesh();

	void render() const;
};

