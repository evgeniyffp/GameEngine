#pragma once

#include <Engine/ECS/Components/CameraComponent.h>
#include <Engine/ECS/Components/TransformComponent.h>

#include <Engine/Core/InputControl/KeyboardControl.h>
#include <Engine/Core/InputControl/MouseControl.h>

class CameraController {
public:
    virtual ~CameraController() = default;

    virtual void update_keyboard_input(CameraComponent& camera_component, TransformComponent& transform, KeyboardControl& keyboard_control, float dt) = 0;

    virtual void update_mouse_input(CameraComponent& camera_component, TransformComponent& transform, MouseControl& mouse_control) = 0;
};

