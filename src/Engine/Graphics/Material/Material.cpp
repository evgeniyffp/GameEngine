#include "Material.h"

Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 color, bool useTexture)
        : ambient(ambient), diffuse(diffuse), specular(specular), color(color), useTexture(useTexture) {}

glm::vec3 Material::getColor() const {
    return color;
}
void Material::setColor(const glm::vec3& new_color) {
    color = new_color;
}
void Material::doColor(const glm::vec3& delta_color) {
    color += delta_color;
}

