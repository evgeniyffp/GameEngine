#pragma once

#include <entt/entt.hpp>

#include <Engine/ECS/Components/CameraControllerComponent.h>

namespace CameraControllerSystem {
    inline void update(entt::registry& registry, entt::entity active_camera, KeyboardControl& keyboard_control, MouseControl& mouse_control, float dt) {
        if (!registry.all_of<CameraControllerComponent>(active_camera))
            return;

        auto& camera = registry.get<CameraComponent>(active_camera);
        auto& transform = registry.get<TransformComponent>(active_camera);

        auto& camera_controller = *registry.get<CameraControllerComponent>(active_camera).camera_controller;

        camera_controller.update_keyboard_input(camera, transform, keyboard_control, dt);
        camera_controller.update_mouse_input(camera, transform, mouse_control);
    }
}

