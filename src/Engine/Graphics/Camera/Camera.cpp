#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>

#include <Time/TimeFromLastFrame.h>

void Camera::updateCameraVectors() {
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));

	front = normalize(front);
	rigth = normalize(cross(front, wordlUp));
	up = normalize(cross(rigth, front));
}

vec3 Camera::getPosition() const {
    return position;
}
void Camera::setPosition(const vec3& new_position) {
    position = new_position;
}
void Camera::move(const vec3& delta_position) {
    position += delta_position;
}

vec3 Camera::getRotation() const {
    return vec3(pitch, yaw, roll);
}

void Camera::setRotation(const vec3& new_rotation) {
    pitch = new_rotation.x;
    yaw = new_rotation.y;
    roll = new_rotation.z;
    
    pitch = clamp(pitch, -80.0, 80.0);
    
    if (yaw < 0) yaw += 360.0;
    if (yaw >= 360.0) yaw -= 360.0;
    
    // updateCameraVectors();
}

void Camera::rotate(const vec3& delta_rotation) {
    pitch += delta_rotation.x;
    yaw += delta_rotation.y;
    roll += delta_rotation.z;
    
    pitch = clamp(pitch, -80.0, 80.0);
    
    if (yaw < 0) yaw += 360.0;
    if (yaw >= 360.0) yaw -= 360.0;
    
    // updateCameraVectors();
}

void Camera::move_in_direction(const Direction direction) {
	auto dt = deltaTime::get();

	switch (direction) {
	case Direction::Forward:
		position.x += movementSpeed * dt * front.x;
		position.z += movementSpeed * dt * front.z;
		break;

	case Direction::Backward:
		position.x -= movementSpeed * dt * front.x;
		position.z -= movementSpeed * dt * front.z;
		break;

	case Direction::Right:
		position += movementSpeed * dt * rigth;
		break;

	case Direction::Left:
		position -= movementSpeed * dt * rigth;
		break;

	case Direction::Up:
		position.y -= movementSpeed * dt;
		break;

	case Direction::Down:
		position.y += movementSpeed * dt;
		break;

	default:
		break;
	}
}

void Camera::updateMouseInput(const dvec2& offset) {
	auto dt = deltaTime::get();

	yaw += sensitivity * dt * offset.x;
	pitch += sensitivity * dt * offset.y;

	pitch = clamp(pitch, -80.0, +80.0);

	if (yaw < -360.0 || yaw > 360.0)
		yaw = 0;
}

Camera::Camera(
	vec3 position, 
	vec3 wordlUp,
    double movementSpeed
) : position(position), wordlUp(wordlUp), up(wordlUp), movementSpeed(movementSpeed)
{
	viewMatrix = mat4(1.0f);

	sensitivity = 4.0f;

	rigth = vec3(0.0f);

	pitch = 0.0f;
	yaw = -90.0f;
	roll = 0.0f;

	updateCameraVectors();
}

void Camera::update(const dvec2& offset) {
	viewMatrix = lookAt(
		position,
		position + front,
		up
	);

	updateCameraVectors();
	updateMouseInput(offset);
}
