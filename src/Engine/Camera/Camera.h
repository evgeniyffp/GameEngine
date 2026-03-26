#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <Engine/Interfaces/Movable.h>

class Camera : public Movable {
private:
    glm::mat4 viewMatrix;

    glm::vec3 position;
    glm::vec3 worldUp;

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 rigth;

	double pitch;
	double yaw;
 
    void normalize_rotation();

public:
    friend class Shader; // TODO
    
    Camera(glm::vec3 position, glm::vec3 worldUp); 
    
    void updateCameraVectors();

    void update();

    glm::vec3 getPosition() const override;
    void setPosition(const glm::vec3& new_position) override;
    void move(const glm::vec3& delta_position) override;
    
    glm::vec2 getRotation() const;
    void setRotation(const glm::vec2& new_rotation);
    void rotate(const glm::vec2& delta_rotation);
    
    glm::vec3 getFront() const;
    glm::vec3 getUp() const;
    glm::vec3 getRigth() const;

    glm::mat4 getViewMatrix() const;
    void setViewMatrix(glm::mat4 new_view_matrix);
    void updateViewMatrix();
};

