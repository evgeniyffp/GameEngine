#include "./Dron.h"

#include <glm/ext/matrix_transform.hpp>

void Dron::move_in_direction(const Direction direction, float dt) {}

void Dron::updateMouseInput(const glm::vec2& offset) {
	camera.rotate(sensitivity * offset);
}

void Dron::update(const glm::vec2& offset, float dt) {
    updateMouseInput(offset + prev_offset);
	prev_offset += offset * 0.2f; prev_offset *= 0.95f;
    camera.update();	
	camera.move(movementSpeed * dt * camera.getFront());
}

