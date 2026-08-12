#include "./Renderer.h"

#include <Engine/Utilities/Setting/Setting.h>

#include <Engine/ECS/Systems/RenderSystem.h>

#include <utils/Log.h>

void Renderer::setClearColor(const glm::vec3& sky_color) {
    glClearColor(sky_color.r, sky_color.g, sky_color.b, 1.0f);
}

void Renderer::beginFrame() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::draw(const SceneStorage& scene_storage, const Shader& shader) const {
    auto cycle = [&](const std::string&, const Scene& scene) {
        RenderSystem::update(scene.getRegistry(), shader);
    };

    scene_storage.for_each(cycle);
}

void Renderer::endFrame(Window& window) const  {
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

    setClearColor(sky_color);
}

void Renderer::render(Window& window, const SceneStorage& scene_storage, const Shader& shader) const {
    beginFrame();
    draw(scene_storage, shader);
    endFrame(window);
}

