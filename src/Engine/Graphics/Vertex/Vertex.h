#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
using namespace glm;

struct Vertex {
	vec3 position;
	vec3 color;
	vec2 texcoord;
	vec3 normal;
};

