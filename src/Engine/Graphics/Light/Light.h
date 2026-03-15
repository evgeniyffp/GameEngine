#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <Engine/Graphics/Transformable/Transformable.h>

class Light : public Transformable {
private:
	float intensity;

	vec3 position;
	vec3 color;

	float constant;
	float linear;
	float quadratic;

public:
	friend class Shader;

	Light(
		vec3 position,

		float intensity = 100.0f,
		vec3 color = vec3(1.0f),

		float constant = 1.0f,
		float linear = 0.045f,
		float quadratic = 0.0075f
	);

    vec3 getPosition() const override;
    void setPosition(const vec3& new_position) override;
    void move(const vec3& delta_position) override;
    
    // TODO
    vec3 getRotation() const override;
    void setRotation(const vec3& new_rotation) override;
    void rotate(const vec3& delta_position) override;
};

