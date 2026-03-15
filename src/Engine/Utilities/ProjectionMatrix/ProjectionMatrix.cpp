#include "ProjectionMatrix.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

ProjectionMatrix::ProjectionMatrix(
	ivec2& size,

	float fov,
	float nearPlane,
	float farPlane

) : size(size), fov(fov), nearPlane(nearPlane), farPlane(farPlane) 
{
	update();
}
void ProjectionMatrix::update()
{
    projectionMatrix = mat4(1.0f);
    
    // Защита от деления на ноль
    float aspect;
    if (size.y == 0.0f) {
        aspect = 1.0f;  // значение по умолчанию
    } else {
        aspect = static_cast<float>(size.x) / size.y;
    }
    
    projectionMatrix = perspective(radians(fov),
            aspect,
            nearPlane,
            farPlane
    );
}
/*void ProjectionMatrix::update()
{
	this->projectionMatrix = mat4(1.0f);
	projectionMatrix = perspective(radians(this->fov),
		float(this->size->x) / this->size->y,
		this->nearPlane,
		this->farPlane
	);
}*/
