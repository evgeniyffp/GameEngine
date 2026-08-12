#pragma once

#include "./CameraController.h"

class BasicCameraController : public CameraController {
private:
    float movement_speed;
    float sensitivity;
   
public:
    BasicCameraController(float movement_speed = 3.f, float sensitivity = 0.07f)
            : movement_speed(movement_speed), sensitivity(sensitivity) {}
    virtual ~BasicCameraController() = default;

    void update_keyboard_input(CameraComponent& camera, TransformComponent& transform, KeyboardControl& keyboard_control, float dt) override {
        glm::vec3 delta_position(0.f);
        glm::vec3 front = camera.front;
        glm::vec3 right = camera.right;

        if (keyboard_control.isPressed("W")) { 
    		delta_position.x += front.x;
    		delta_position.z += front.z;
    	}
        if (keyboard_control.isPressed("S")) { 
    		delta_position.x -= front.x;
    		delta_position.z -= front.z;
    	}
        if (keyboard_control.isPressed("D")) { 
		    delta_position += right;
        }
        if (keyboard_control.isPressed("A")) { 
    		delta_position -= right;
        }
        if (keyboard_control.isPressed("SPACE")) { 
    		delta_position.y += 1;
        }
        if (keyboard_control.isPressed("LEFT_SHIFT")) { 
    		delta_position.y -= 1;
        }

        transform.position_component.position += delta_position * dt * movement_speed;   
    }

    void update_mouse_input(CameraComponent& camera, TransformComponent&, MouseControl& mouse_control) override {
        const glm::vec2 offset = mouse_control.getOffset();

        auto delta_rotation = sensitivity * offset;

        camera.yaw += delta_rotation.x;
        camera.pitch += delta_rotation.y;
     
        camera.normalize_rotation();

        camera.update_vectors();
    }
};

