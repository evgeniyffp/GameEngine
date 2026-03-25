#pragma once

#include <glm/vec3.hpp>

class Rotatable {
public:
    virtual ~Rotatable() = default;

    virtual glm::vec3 getRotation() const = 0;
    virtual void setRotation(const glm::vec3& new_rotation) = 0;
    virtual void rotate(const glm::vec3& delta_rotation) = 0;
};

