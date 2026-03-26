#include "./ProjectionMatrix.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

ProjectionMatrix::ProjectionMatrix(
	glm::ivec2& size,
	float fov,
	float nearPlane,
	float farPlane
) : size(size), fov(fov), nearPlane(nearPlane), farPlane(farPlane) 
{}

void ProjectionMatrix::update()
{
    projectionMatrix = glm::mat4(1.0f);
    
    float aspect;
    if (size.y == 0.0f)
        aspect = 1.0f;
    else
        aspect = static_cast<float>(size.x) / size.y;
    
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

