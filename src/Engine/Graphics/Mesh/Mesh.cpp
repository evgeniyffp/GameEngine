#include "Mesh.h"

void Mesh::init() {
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,
		vertexArray.size() * sizeof(Vertex), vertexArray.data(),
		GL_STATIC_DRAW);

	if (indexArray.size() != 0) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indexArray.size() * sizeof(GLuint), indexArray.data(),
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

Mesh::Mesh(std::vector<Vertex> vertexArray, std::vector<GLuint> indexArray)
        : vertexArray(std::move(vertexArray)), indexArray(std::move(indexArray)) {
	init();
}

Mesh::~Mesh() {
    if (is_clear) return;
	
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	if (indexArray.size() != 0)
		glDeleteBuffers(1, &EBO);
}

void Mesh::render(const Shader& shader) const {
    {
        ShaderUser _su(shader);
        glBindVertexArray(VAO);
        if (indexArray.size() == 0)
        	glDrawArrays(GL_TRIANGLES, 0, vertexArray.size());
        else
        	glDrawElements(GL_TRIANGLES, indexArray.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

