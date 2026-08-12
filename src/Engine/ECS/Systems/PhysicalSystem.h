#pragma once

#include <entt/entt.hpp>

#include <Engine/ECS/Components/TransformComponent.h>
#include <Engine/ECS/Components/PhysicalComponent.h>

namespace PhysicalSystem {
    namespace constants {
        inline glm::vec3 g(0.f, -9.81f, 0.f);
    }

    inline void update(entt::registry& registry, float dt) {
        auto view = registry.view<TransformComponent, PhysicalComponent>();
        
        for (auto entity : view) {
            auto& transform_component = view.get<TransformComponent>(entity);
            auto& physical_component = view.get<PhysicalComponent>(entity);

            transform_component.position_component += physical_component.speed * dt;
            // need collision's processing

            physical_component.speed += constants::g * dt;
        }
    
    }
}

