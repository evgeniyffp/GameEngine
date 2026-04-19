#pragma once

#include <glm/ext/matrix_transform.hpp>

#include <Engine/ECS/Components/CameraComponent.h>

#include <Engine/Shader/Shader.h>

namespace CameraSystem {
    inline void _normalize_rotation(CameraComponent& camera) {
        camera.pitch = glm::clamp(camera.pitch, -80.f, 80.f);
        
        while (camera.yaw < 0.f) camera.yaw += 360.f;
        while (camera.yaw >= 360.f) camera.yaw -= 360.f;
    }

    inline void _update_vectors(CameraComponent& camera) {
        camera.front = glm::normalize(glm::vec3(
            cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch)),
	        sin(glm::radians(camera.pitch)),
	        sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch))
        ));

	    camera.rigth = normalize(cross(camera.front, camera.worldUp));
	    camera.up = normalize(cross(camera.rigth, camera.front));
    }

    inline void update(entt::registry& registry, entt::entity active_camera, const Shader& shader) {
        auto& camera = registry.get<CameraComponent>(active_camera);
        
        camera.viewMatrix = glm::lookAt(
		    camera.position,
		    camera.position + camera.front,
		    camera.up
	    );
    
        ShaderUser _su(shader);
	    shader.setUniform(camera, "camera");
    }
    
    inline void move_in_direction(entt::registry& registry, entt::entity active_camera, const Direction direction, const float dt) {
        float movement_speed = 40.f;

        auto& camera = registry.get<CameraComponent>(active_camera);

        glm::vec3 delta_position(0.f);
        glm::vec3 front = camera.front;
        glm::vec3 rigth = camera.rigth;

    	switch (direction) {
    	case Direction::Forward:
    		delta_position.x += front.x;
    		delta_position.z += front.z;
    		break;

    	case Direction::Backward:
    		delta_position.x -= front.x;
    		delta_position.z -= front.z;
    		break;

    	case Direction::Right:
		    delta_position += rigth;
    		break;

    	case Direction::Left:
    		delta_position -= rigth;
    		break;

    	case Direction::Up:
    		delta_position.y += 1;
    		break;

    	case Direction::Down:
    		delta_position.y -= 1;
    		break;

    	default:
    		break;
    	}

        camera.position += delta_position * dt * movement_speed;   
    }

    inline void update_mouse_input(entt::registry& registry, entt::entity active_camera, const glm::vec2& offset) {
        float sensitivity = 0.07f;

        auto& camera = registry.get<CameraComponent>(active_camera);

        auto delta_rotation = sensitivity * offset;

        camera.yaw += delta_rotation.x;
        camera.pitch += delta_rotation.y;
     
        _normalize_rotation(camera);

        _update_vectors(camera);
    }
}

