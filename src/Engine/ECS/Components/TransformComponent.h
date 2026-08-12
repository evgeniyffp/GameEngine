#pragma once

#include "./PositionComponent.h"
#include "./RotationComponent.h"
#include "./ScaleComponent.h"

struct TransformComponent {
    PositionComponent position_component;
    RotationComponent rotation_component;
    ScaleComponent scale_component;
    glm::vec3 origin = glm::vec3(0.f);
};

