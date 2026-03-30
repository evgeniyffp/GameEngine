#include "./Camera.h"

#include <glm/ext/matrix_transform.hpp>

void Camera::normalize_rotation() {
    pitch = glm::clamp(pitch, -80.f, 80.f);
    
    while (yaw < 0.f) yaw += 360.f;
    while (yaw >= 360.f) yaw -= 360.f;
}

Camera::Camera(glm::vec3 position, glm::vec3 worldUp) 
        : position(position), worldUp(worldUp) {
	viewMatrix = glm::mat4(1.0f);

	rigth = glm::vec3(0.0f);

	pitch = 0.0f;
	yaw = -90.0f;
}

void Camera::updateCameraVectors() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = normalize(front);
	rigth = normalize(cross(front, worldUp));
	up = normalize(cross(rigth, front));
}

void Camera::update() {
    updateCameraVectors();
	updateViewMatrix();
}

glm::vec3 Camera::getPosition() const {
    return position;
}
void Camera::setPosition(const glm::vec3& new_position) {
    position = new_position;
}
void Camera::move(const glm::vec3& delta_position) {
    position += delta_position;
}

glm::vec2 Camera::getRotation() const {
    return glm::vec2(pitch, yaw);
}
void Camera::setRotation(const glm::vec2& new_rotation) {
    pitch = new_rotation.x;
    yaw = new_rotation.y;
    
    normalize_rotation();
}
void Camera::rotate(const glm::vec2& delta_rotation) {
    yaw += delta_rotation.x;
    pitch += delta_rotation.y;
    
    normalize_rotation();
}

glm::vec3 Camera::getFront() const {
    return front;
}
glm::vec3 Camera::getUp() const { 
    return up;
}
glm::vec3 Camera::getRigth() const {
    return rigth;
}

glm::mat4 Camera::getViewMatrix() const {
    return viewMatrix;
}
void Camera::setViewMatrix(glm::mat4 new_view_matrix) { 
    viewMatrix = new_view_matrix;
}
void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(
		position,
		position + front,
		up
	);
}

