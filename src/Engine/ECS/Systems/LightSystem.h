#pragma once

#include <entt/entt.hpp>

#include <Engine/ECS/Components/TransformComponent.h>
#include <Engine/ECS/Components/LightComponent.h>

#include <Engine/Shader/Shader.h>

namespace LightSystem {
    inline void update(entt::registry& registry, const Shader& shader) {
        std::vector<std::pair<TransformComponent, LightComponent>> lights;
        
        auto view = registry.view<TransformComponent, LightComponent>();
        for (auto entity : view) {
            lights.emplace_back(view.get<TransformComponent>(entity), view.get<LightComponent>(entity));
        }
    
        ShaderUser _su(shader);
        shader.setUniformArray(lights, "u_lights");
    }
}

