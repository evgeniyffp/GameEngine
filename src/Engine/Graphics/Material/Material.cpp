#include "Material.h"

Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, bool useTexture)
        : ambient(ambient), diffuse(diffuse)
        , specular(specular), useTexture(useTexture) {}

