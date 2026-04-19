#pragma once

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

class ProjectionMatrix {
private:
    glm::ivec2& size;

	float fov;
	float nearPlane;
	float farPlane;
	
    glm::mat4 projectionMatrix;

public:
	ProjectionMatrix(
		glm::ivec2& size,

		float fov = 90,
		float nearPlane = 0.001f,
		float farPlane = 1000
	);

    glm::mat4 get() const;
	void update();
};

