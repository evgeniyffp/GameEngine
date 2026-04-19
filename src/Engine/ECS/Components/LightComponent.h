#pragma once

#include <glm/vec3.hpp>

struct LightComponent {
	float intensity = 100.0f;
	glm::vec3 color = glm::vec3(1.0f);

	float constant = 1.0f;
	float linear = 0.045f;
	float quadratic = 0.0075;
};

