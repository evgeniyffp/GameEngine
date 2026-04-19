#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

// TODO unused ??
enum class Direction {
	Forward, Backward,
	Left, Right,
	Up, Down
};

struct CameraComponent {
    glm::vec3 position;
    glm::vec3 worldUp;

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 rigth;

	float pitch = 0.f;
	float yaw = -90.f;
    
    glm::mat4 viewMatrix = glm::mat4(1.f);
};

