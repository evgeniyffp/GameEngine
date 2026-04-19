#include "./Renderer.h"

#include <Engine/Utilities/Setting/Setting.h>

#include <utils/Log.h>

void Renderer::set_clear_color(const glm::vec3& sky_color) {
    glClearColor(sky_color.r, sky_color.g, sky_color.b, 1.0f);
}

void Renderer::begin_frame() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::draw_scene(const entt::registry& registry, const Shader& shader) const {
    RenderSystem::update(registry, shader);
}

void Renderer::end_frame(Window& window) const  {
	glfwSwapBuffers(window.get());

	glBindVertexArray(0);

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::init(const glm::vec3& sky_color) {
	GLSetting::Version::set(4, 5);
    
    std::string info = "Renderer.cpp => Renderer::init() => gladLoadGLLoader";

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Log::critical(info);
        throw info;
    }

    Log::debug(info);

    glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GLSetting::DefaultRenderMode);

    set_clear_color(sky_color);
}

void Renderer::render(Window& window, const entt::registry& registry, const Shader& shader) const {
    begin_frame();
    draw_scene(registry, shader);
    end_frame(window);
}

