#pragma once

#include <glm/vec3.hpp>
using namespace glm;

class Material {
private:
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	bool useTexture;

public:
	friend class Model;
	friend class Shader;

	Material(vec3 ambient, vec3 diffuse, vec3 specular, bool useTexture = true);
};

