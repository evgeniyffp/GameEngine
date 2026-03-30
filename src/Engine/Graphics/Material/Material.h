#pragma once

#include <glm/vec3.hpp>
using namespace glm;

#include <Engine/Interfaces/Colorable.h>

class Material : public Colorable {
private:
	vec3 ambient;
	
    vec3 diffuse;
	vec3 specular;

	bool useTexture;
    vec3 color;

public:
	friend class Model;
	friend class Shader;

	Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 color = vec3(1.0f), bool useTexture = true);

    glm::vec3 getColor() const override;
    void setColor(const glm::vec3& new_color) override;
    void doColor(const glm::vec3& delta_color) override;
};

