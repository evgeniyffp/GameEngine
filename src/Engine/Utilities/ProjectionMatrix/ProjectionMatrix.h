#ifndef PROJECTION_MATRIX_H
#define PROJECTION_MATRIX_H

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
using namespace glm;

class ProjectionMatrix {
private:
	ivec2& size;

	float fov;
	float nearPlane;
	float farPlane;
	mat4 projectionMatrix;

public:
	friend class Shader;

	ProjectionMatrix(
		ivec2& size,

		float fov = 90,
		float nearPlane = 0.001f,
		float farPlane = 1000
	);

	void update();
};

#endif
