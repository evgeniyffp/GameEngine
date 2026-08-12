#pragma once

#include <vector>

#include "./ModelPartComponent.h"

struct ModelComponent {
    ModelComponent(ModelComponent&&) = default;
    ModelComponent() = default;

    std::vector<ModelPartComponent> parts;
    std::string file_name;
};

