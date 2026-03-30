#pragma once

#include <Engine/Camera/CameraController.h>

class Dron : public CameraController {
private:
    float movementSpeed;
	float sensitivity;

    glm::vec2 prev_offset;

    void updateMouseInput(const glm::vec2& offset);

public:
    Dron(Camera& camera, float movementSpeed, float sensitivity = 0.07)
            : CameraController(camera), movementSpeed(movementSpeed), sensitivity(sensitivity) {}
    
    ~Dron() override = default;

	void move_in_direction(const Direction direction, float dt) override;

	void update(const glm::vec2& offset, float dt) override;
};

