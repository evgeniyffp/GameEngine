#pragma once

#include <glm/vec3.hpp>

#include <entt/entt.hpp>

#include <Engine/Shader/Shader.h>
#include <Engine/Core/Window/Window.h>
#include <Engine/ECS/Systems/RenderSystem.h>

class Renderer {
private:
    void set_clear_color(const glm::vec3& color);

    void begin_frame() const;

    void draw_scene(const entt::registry& registry, const Shader& shader) const;

    void end_frame(Window& window) const;

public:
    void init(const glm::vec3& sky_color);

    void render(Window& window, const entt::registry& registry, const Shader& shader) const;
};

