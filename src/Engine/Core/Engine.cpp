#include "Engine.h"

#include <Engine/Utilities/Setting/Setting.h>

#include <utils/displayInfo.h>

void Engine::initGLAD() {
	if (isInitGLAD)
        return;

    std::string info = "Engine.cpp => Engine::initGLAD() => gladLoadGLLoader";
    displayInfo(info);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw info;
    }

	isInitGLAD = true;

    glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //
	glPolygonMode(GL_FRONT_AND_BACK, GLSetting::DefaultRenderMode);

    //
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);	
}

void Engine::loop() {
	while (!window.is_closed()) {
		update();
		render();
	}
}

Engine::Engine(std::string title)
        : window(std::move(title)), projectionMatrix(window.get_size_ref()) {
	GLSetting::Version::set(4, 5);
	
	window.init();

    initGLAD();
}

void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	world.render(shaders[Shader_Core_Program]);

	glfwSwapBuffers(window.get());
	glFlush();

	glBindVertexArray(0);

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

