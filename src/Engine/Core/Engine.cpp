#include "Engine.h"

#include <Engine/Utilities/Setting/Setting.h>

#include <Time/Time.h>

#include <utils/Log.h>

void Engine::initGLAD() {
	if (isInitGLAD)
        return;

    std::string info = "Engine.cpp => Engine::initGLAD() => gladLoadGLLoader";

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Log::critical(info);
        glfwTerminate();
        throw info;
    }

    Log::debug(info);
	isInitGLAD = true;

    glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GLSetting::DefaultRenderMode);

    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);	
}

void Engine::initUniforms() {
    ShaderUser _su(shaders[Shader_Core_Program]);
	
    shaders[Shader_Core_Program].setUniform(projectionMatrix, "projectionMatrix");
}

void Engine::updateUniforms() {
    ShaderUser _su(shaders[Shader_Core_Program]);
	
    shaders[Shader_Core_Program].setUniformArray(lights, "u_lights");

	shaders[Shader_Core_Program].setUniform(cameraControllers[selectedCameraController]->get(), "camera");
}

void Engine::addShader(const std::string& vertex_filename, const std::string& fragment_filename) {
	shaders.emplace_back(vertex_filename, fragment_filename);
}

void Engine::loop() {
    initUniforms();

    float dt = 0;

	while (!window.is_closed()) {
        Profiler profiler;
        profiler.start("frame");

        profiler.start("update");
        update(dt);
        profiler.end("update");
		
        profiler.start("updateUniforms");
        updateUniforms();
        profiler.end("updateUniforms");

        profiler.start("render");
        render();
        profiler.end("render");

        profiler.end("frame");

        dt = profiler.get("frame");

        // profiler info
        std::vector<std::string> names { "render", "update", "updateUniforms" };

        for (const auto& name : names) {
            Log::debug("* {}:\t{}ms,\t{}%", name, profiler.get(name) * 1000, profiler.get(name) / dt * 100);
        }
        
        vec3 camera_pos = cameraControllers[selectedCameraController]->get().getPosition();
        Log::debug("Selected camera position - x:{}, y:{}, z:{}", camera_pos.x, camera_pos.y, camera_pos.z);

        float addition_time = 1 / FPS - dt;
        if (addition_time > 0.0f) {
            Core::Time::sleep(addition_time);
            dt = 1 / FPS;
        }
    }
}

Engine::Engine(std::string title)
        : window(std::move(title)), projectionMatrix(window.get_size_ref()) {
	GLSetting::Version::set(4, 5);

	window.init();

    initGLAD();
}

KeyboardControl& Engine::getKeyboardControl() {
    return window.getKeyboardControl();
}

MouseControl& Engine::getMouseControl() {
    return window.getMouseControl();
}

void Engine::close() {
    window.close();
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

