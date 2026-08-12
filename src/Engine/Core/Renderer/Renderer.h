#pragma once

#include <glm/vec3.hpp>

#include <entt/entt.hpp>

#include <Engine/Shader/Shader.h>

#include <Engine/Core/Window/Window.h>
#include <Engine/Core/Scene/SceneStorage.h>

class Renderer {
private:
    void setClearColor(const glm::vec3& color);

    void beginFrame() const;

    void draw(const SceneStorage& registry, const Shader& shader) const;

    void endFrame(Window& window) const;

public:
    void init(const glm::vec3& sky_color);

    void render(Window& window, const SceneStorage& registry, const Shader& shader) const;
};

