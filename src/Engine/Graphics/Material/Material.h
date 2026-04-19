#pragma once

#include <memory>
#include <glm/vec3.hpp>

#include <Engine/Graphics/Texture/Texture.h>

class Material {
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 color;

    std::shared_ptr<Texture> diffuse_texture;
    std::shared_ptr<Texture> specular_texture;

public:
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color = glm::vec3(1.0f));

    Material(const Material&) = default;
    Material& operator=(const Material&) = default;

    Material(Material&&) = default;
    Material& operator=(Material&&) = default;

    void setDiffuseTexture(std::shared_ptr<Texture> texture);
    void setSpecularTexture(std::shared_ptr<Texture> texture);

    void bind() const;

    bool isUseTexture() const;

    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;

    glm::vec3 getColor() const;
    void setColor(const glm::vec3& new_color);
    void doColor(const glm::vec3& delta_color);
};
