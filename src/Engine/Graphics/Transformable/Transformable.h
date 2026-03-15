#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
using namespace glm;

class Transformable {
public:
    virtual ~Transformable() = default;

    virtual vec3 getPosition() const = 0;
    virtual void setPosition(const vec3& pos) = 0;
    virtual void move(const vec3& delta) = 0;
    
    virtual vec3 getRotation() const = 0;
    virtual void setRotation(const vec3& rot) = 0;
    virtual void rotate(const vec3& delta) = 0;
    
    // virtual vec3 getScale() const = 0;
    // virtual void setScale(const vec3& scale) = 0;
};

