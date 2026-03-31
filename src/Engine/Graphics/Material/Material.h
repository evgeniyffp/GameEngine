#pragma once

#include <glm/vec3.hpp>

#include <Engine/Graphics/Texture/Texture.h>

#include <Engine/Interfaces/Colorable.h>

class Material : public Colorable {
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    glm::vec3 color;

    Texture diffuse_texture;
    Texture specular_texture;

public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color = glm::vec3(1.0f));

    void setDiffuseTexture(Texture texture);
    void setSpecularTexture(Texture texture);

    void bind() const;

    bool isUseTexture() const;

    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;

    glm::vec3 getColor() const override;
    void setColor(const glm::vec3& new_color) override;
    void doColor(const glm::vec3& delta_color) override;
};

