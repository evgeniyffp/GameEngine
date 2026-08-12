#pragma once

#include <entt/entt.hpp>

#include <glm/ext/matrix_transform.hpp>

#include <Engine/ECS/Components/CameraComponent.h>

#include <Engine/Shader/Shader.h>

namespace CameraSystem {
    inline void update(entt::registry& registry, entt::entity active_camera, const Shader& shader) {
        auto& camera = registry.get<CameraComponent>(active_camera);
        auto& transform = registry.get<TransformComponent>(active_camera);
 
        const auto& position = transform.position_component.position;

        glm::mat4 viewMatrix = glm::lookAt(
		    position,
		    position + camera.front,
		    camera.up
	    );

        {
            ShaderUser _su(shader);

            shader.setUniform(viewMatrix, "viewMatrix");
    	    shader.setUniform(position, "camera.position");
        }
    }
}

