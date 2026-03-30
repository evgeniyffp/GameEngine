#pragma once

#include <Engine/Camera/Camera.h>

enum class Direction {
	Forward, Backward,
	Left, Right,
	Up, Down
};

// TODO Movable
class CameraController {
protected:
    Camera& camera;
	
public:
    CameraController(Camera& camera) : camera(camera) {}
    virtual ~CameraController() = default;

    Camera& get() { return camera; }

	virtual void move_in_direction(const Direction direction, float dt) = 0;

	virtual void update(const glm::vec2& offset, float dt) = 0;
};

