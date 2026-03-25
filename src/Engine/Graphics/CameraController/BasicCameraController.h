#pragma once

#include "./CameraController.h"

// TODO Movable
class BasicCameraController : public CameraController {
private:
    double movementSpeed;
	double sensitivity;

    void updateMouseInput(const glm::dvec2& offset);

public:
    BasicCameraController(Camera& camera, double movementSpeed, double sensitivity = 0.07)
            : CameraController(camera), movementSpeed(movementSpeed), sensitivity(sensitivity) {}
    
    ~BasicCameraController() override = default;

	void move_in_direction(const Direction direction, double dt) override;

	void update(const glm::dvec2& offset, double dt) override;
};

