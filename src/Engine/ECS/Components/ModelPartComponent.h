#pragma once

#include <Engine/Graphics/Mesh/Mesh.h>
#include <Engine/Graphics/Material/Material.h>

#include <glm/mat4x4.hpp>

struct ModelPartComponent {
    Mesh mesh;
    Material material;
    glm::mat4 relative_matrix = glm::mat4(1.0f);
};

