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

glm::vec3 Light::getColor() const {
    return color;
}
void Light::setColor(const glm::vec3& new_color) {
    color = new_color;
}
void Light::doColor(const glm::vec3& delta_color) {
    color += delta_color;
}

