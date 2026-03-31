#include "Texture.h"

#include <exception>

#include <soil2/SOIL2.h>

#include <utils/Log.h>

Texture::Texture() : empty(true) {}

Texture::Texture(const std::string& imageFile, GLenum typeTexture) : typeTexture(typeTexture) {
	loadFromFile(imageFile);
}

Texture& Texture::operator=(Texture&& other) {
    id = std::move(other.id);
    typeTexture = std::move(other.typeTexture);
    size = std::move(other.size);
    
    empty = false; other.empty = true;

    return *this;
}

Texture::Texture(Texture&& other) : id(other.id), typeTexture(other.typeTexture), size(other.size)  {
    other.empty = true;
}

Texture::~Texture() {
    if (!empty)
        glDeleteTextures(1, &id);
}

bool Texture::is_empty() const { 
    return empty;
}

GLuint Texture::get_id() const { 
    return id; 
}

void Texture::loadFromFile(const std::string& imageFile) {
	if (id)
		glDeleteTextures(1, &id);
	
	unsigned char* image = SOIL_load_image(imageFile.c_str(),
		&size.x, &size.y,
		NULL, SOIL_LOAD_RGBA);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(typeTexture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(typeTexture, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(typeTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(typeTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	std::string info = "Texture.h => Texture::loadFromFile() => SOIL_load_image() => Image \"" + imageFile + "\" load";
	
    if (!image) {
        Log::error(info);
		throw info.c_str();
    }
    Log::debug(info);
		
    glTexImage2D(typeTexture, 0, GL_RGBA,
	    size.x, size.y,
		0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glActiveTexture(0);
	glBindTexture(typeTexture, id);

	SOIL_free_image_data(image);
}

void Texture::bind(const GLint textureUnit) const  {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(typeTexture, id);
}

void Texture::unBind() const {
	glActiveTexture(0);
	glBindTexture(typeTexture, 0);
}

