#pragma once

#include <entt/entt.hpp>

#include <Engine/Shader/Shader.h>

namespace RenderSystem {
    void update(const entt::registry& registry, const Shader& shader);
}

