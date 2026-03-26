#pragma once

#include <Engine/Camera/CameraController.h>

class Dron : public CameraController {
private:
    double movementSpeed;
	double sensitivity;

    glm::dvec2 prev_offset;

    void updateMouseInput(const glm::dvec2& offset);

public:
    Dron(Camera& camera, double movementSpeed, double sensitivity = 0.07)
            : CameraController(camera), movementSpeed(movementSpeed), sensitivity(sensitivity) {}
    
    ~Dron() override = default;

	void move_in_direction(const Direction direction, double dt) override;

	void update(const glm::dvec2& offset, double dt) override;
};

