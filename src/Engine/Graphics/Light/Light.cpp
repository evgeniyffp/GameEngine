#include "Light.h"

Light::Light(
	vec3 position, 

	float intensity, 
	vec3 color, 
	
	float constant, 
	float linear, 
	float quadratic

) :
	position(position),

	intensity(intensity),
	color(color),

	constant(constant),
	linear(linear),
	quadratic(quadratic)
{}

vec3 Light::getPosition() const {
    return position;
}
void Light::setPosition(const vec3& new_position) {
    position = new_position;
}
void Light::move(const vec3& delta_position) {
    position += delta_position;
}

// TODO
vec3 Light::getRotation() const { return vec3(0, 0, 0); }
void Light::setRotation(const vec3& new_rotation) {}
void Light::rotate(const vec3& delta_position) {}

