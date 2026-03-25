#pragma once

#include <glm/vec3.hpp>

class Scalable {
public:
    virtual ~Scalable() = default;

    virtual glm::vec3 getScale() const = 0;
    virtual void setScale(const glm::vec3& new_scale) = 0;
    virtual void doScale(const glm::vec3& delta_scale) = 0;
};

