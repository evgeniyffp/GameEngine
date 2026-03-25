#pragma once

#include <glm/vec3.hpp>

class Movable {
public:
    virtual ~Movable() = default;

    virtual glm::vec3 getPosition() const = 0;
    virtual void setPosition(const glm::vec3& new_position) = 0;
    virtual void move(const glm::vec3& delta_position) = 0;
};

