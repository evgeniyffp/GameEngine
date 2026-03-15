#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
using namespace glm;

#include <Engine/Graphics/Transformable/Transformable.h>

enum class Direction {
	Forward, Backward,
	Left, Right,
	Up, Down
};

class Camera : public Transformable {
private:
	mat4 viewMatrix;
	
    double movementSpeed;
	double sensitivity;
	
    dvec3 position;
    dvec3 wordlUp;

	dvec3 front;
	dvec3 up;
	dvec3 rigth;

	double pitch;
	double yaw;
	double roll;

	void updateCameraVectors();

	void updateMouseInput(const dvec2& offset);

public:
	friend class Shader;

	Camera(
		vec3 position,
		vec3 wordlUp,
        double movementSpeed
	);
    
    vec3 getPosition() const override;
    void setPosition(const vec3& new_position) override;
    void move(const vec3& delta_position) override;
    
    vec3 getRotation() const override;
    void setRotation(const vec3& new_rotattion) override;
    void rotate(const vec3& delta_rotation) override;
 
	void move_in_direction(const Direction direction);

	void update(const dvec2& offset);

};

