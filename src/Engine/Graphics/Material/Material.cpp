#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color)
        : ambient(ambient), diffuse(diffuse), specular(specular), color(color) {}

void Material::setDiffuseTexture(Texture texture) {
    diffuse_texture = std::move(texture);
}

void Material::setSpecularTexture(Texture texture) {
    specular_texture = std::move(texture);
}

void Material::bind() const {
    if (!diffuse_texture.is_empty()) {
        diffuse_texture.bind(0);
    }
    if (!specular_texture.is_empty()) {
        specular_texture.bind(1);
    }
}

bool Material::isUseTexture() const {
    return !diffuse_texture.is_empty();
}

glm::vec3 Material::getAmbient() const {
    return ambient;
}
glm::vec3 Material::getDiffuse() const {
    return diffuse;
}
glm::vec3 Material::getSpecular() const {
    return specular;
}

glm::vec3 Material::getColor() const {
    return color;
}
void Material::setColor(const glm::vec3& new_color) {
    color = new_color;
}
void Material::doColor(const glm::vec3& delta_color) {
    color += delta_color;
}

