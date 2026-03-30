#include "./BasicCameraController.h"

#include <glm/ext/matrix_transform.hpp>

void BasicCameraController::move_in_direction(const Direction direction, float dt) {
    glm::vec3 delta_position{};
    glm::vec3 front = camera.getFront();
    glm::vec3 rigth = camera.getRigth();

	switch (direction) {
	case Direction::Forward:
		delta_position.x += movementSpeed * dt * front.x;
		delta_position.z += movementSpeed * dt * front.z;
		break;

	case Direction::Backward:
		delta_position.x -= movementSpeed * dt * front.x;
		delta_position.z -= movementSpeed * dt * front.z;
		break;

	case Direction::Right:
		delta_position += movementSpeed * dt * rigth;
		break;

	case Direction::Left:
		delta_position -= movementSpeed * dt * rigth;
		break;

	case Direction::Up:
		delta_position.y += movementSpeed * dt;
		break;

	case Direction::Down:
		delta_position.y -= movementSpeed * dt;
		break;

	default:
		break;
	}

    camera.move(delta_position);
}

void BasicCameraController::updateMouseInput(const glm::vec2& offset) {
	camera.rotate(sensitivity * offset);
}

void BasicCameraController::update(const glm::vec2& offset, float) {
	updateMouseInput(offset);
    camera.update();	
}

