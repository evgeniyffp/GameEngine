#pragma once

#include <Engine/Camera/CameraController.h>

// TODO Movable
class BasicCameraController : public CameraController {
private:
    float movementSpeed;
	float sensitivity;

    void updateMouseInput(const glm::vec2& offset);

public:
    BasicCameraController(Camera& camera, float movementSpeed, float sensitivity = 0.07f)
            : CameraController(camera), movementSpeed(movementSpeed), sensitivity(sensitivity) {}
    
    ~BasicCameraController() override = default;

	void move_in_direction(const Direction direction, float dt) override;

	void update(const glm::vec2& offset, float dt) override;
};

