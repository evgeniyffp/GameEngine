#pragma once

#include <glm/vec3.hpp>

struct PhysicalComponent {
    float mass;
    glm::vec3 speed = glm::vec3(0.f);

    bool is_gravity = true;
    bool is_collision = true;
};

