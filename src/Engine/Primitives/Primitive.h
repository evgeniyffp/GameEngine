#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <Engine/Graphics/Vertex/Vertex.h>

class Primitiv
{
private:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;

public:
	friend class Mesh;

	void set(
		const Vertex* vertices, GLuint countVertices,
		const GLuint* indices, GLuint countIndeces
	)
	{
		for (GLuint i = 0; i < countVertices; ++i)
			this->vertices.push_back(vertices[i]);
		for (GLuint i = 0; i < countIndeces; ++i)
			this->indices.push_back(indices[i]);
	}

	Vertex* getVertices() { return this->vertices.data(); }
	GLuint* getIndices() { return this->indices.data(); }

	const size_t getCountVertices() { return this->vertices.size(); }
	const size_t getCountIndeces() { return this->indices.size(); }
};

#endif
