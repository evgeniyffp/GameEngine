#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/vec2.hpp>

constexpr auto TEXTURE_1D = GL_TEXTURE_1D;
constexpr auto TEXTURE_2D = GL_TEXTURE_2D;
constexpr auto TEXTURE_3D = GL_TEXTURE_3D;

class Texture {
private:
    bool empty = false;
	GLuint id;

	GLenum typeTexture;

    glm::ivec2 size;

public:
    Texture();
	Texture(const std::string& imageFile, GLenum typeTexture);

    Texture(const Texture&) = delete;
    
    Texture& operator=(Texture&& texture);
    Texture(Texture&& other);

	~Texture();

    bool is_empty() const;

    GLuint get_id() const;

	void loadFromFile(const std::string& imageFile);

	void bind(const GLint textureUnit) const;
	void unBind() const;
};

