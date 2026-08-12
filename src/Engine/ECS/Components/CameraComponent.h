#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

enum class Direction {
	Forward, Backward,
	Left, Right,
	Up, Down
};

struct CameraComponent {
    glm::vec3 worldUp;

	float pitch = 0.f;
	float yaw = -90.f;   
 
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
   
    void normalize_rotation() {
        pitch = glm::clamp(pitch, -80.f, 80.f);

        while (yaw < 0.f) yaw += 360.f;
        while (yaw >= 360.f) yaw -= 360.f;
    }

    void update_vectors() {
        front = glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
	        sin(glm::radians(pitch)),
	        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        );

	    right = glm::normalize(glm::cross(front, worldUp));
	    up = glm::normalize(glm::cross(right, front));
    }
};

