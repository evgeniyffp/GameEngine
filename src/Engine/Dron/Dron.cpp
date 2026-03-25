#include "./Dron.h"

#include <glm/ext/matrix_transform.hpp>

#include <Time/TimeFromLastFrame.h>

void Dron::move_in_direction(const Direction direction, double dt) {}

void Dron::updateMouseInput(const glm::dvec2& offset) {
	camera.rotate(sensitivity * offset);
}

void Dron::update(const glm::dvec2& offset, double dt) {
    updateMouseInput(offset + prev_offset);
	prev_offset += offset * 0.2; prev_offset *= 0.95;
    camera.update();	
	camera.move(movementSpeed * dt * glm::dvec3(camera.getFront()));
}

