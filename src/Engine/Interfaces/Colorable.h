#pragma once

#include <glm/vec3.hpp>

class Colorable {
public:
    virtual ~Colorable() = default;

    virtual glm::vec3 getColor() const = 0;
    virtual void setColor(const glm::vec3& new_color) = 0;
    virtual void doColor(const glm::vec3& delta_color) = 0;
};

