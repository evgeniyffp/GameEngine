#include "Engine.h"

#include <Engine/ECS/Systems/LightSystem.h>
#include <Engine/ECS/Systems/CameraSystem.h>

#include <Time/Time.h>

#include <Time/Profiler.h>

#include <utils/Log.h>

void Engine::initUniforms() {
    ShaderUser _su(*shader);

    shader->setUniform(projectionMatrix, "projectionMatrix");
}

void Engine::setShader(const std::string& vertex_filename, const std::string& fragment_filename) {
	shader = std::make_unique<Shader>(vertex_filename, fragment_filename);
}

void Engine::loop() {
	projectionMatrix.update();
    initUniforms();

    float dt = 0;

	while (!window.is_closed()) {
        Profiler profiler;
        profiler.start("frame");

        profiler.start("update window");
        window.update();
        profiler.end("update window");

        profiler.start("update");
        update(dt);
        profiler.end("update");
		
        profiler.start("Systems update");
        LightSystem::update(registry, *shader);
        CameraSystem::update(registry, active_camera, *shader);
        
        auto mouse_offset = getMouseControl().getOffset();
        CameraSystem::update_mouse_input(registry, active_camera, mouse_offset);
        profiler.end("Systems update");

        profiler.start("render");
        render();
        profiler.end("render");

        profiler.end("frame");

        dt = profiler.get("frame");

        // profiler info
        std::vector<std::string> names { "render", "update", "update window", "Systems update", "frame" };

        float all_perc = 0.f;

        for (const auto& name : names) {
            float perc = profiler.get(name) / dt * 100;
            all_perc += perc;
            Log::debug("* {}:\t{}ms,\t{}%", name, profiler.get(name) * 1000, perc);
       }
      
        const auto& camera = registry.get<CameraComponent>(active_camera);

        glm::vec3 camera_pos = camera.position;
        Log::debug("Selected camera position - x:{}, y:{}, z:{}", camera_pos.x, camera_pos.y, camera_pos.z);
        
        Log::debug("Selected camera rotation - x:{}, y:{}", camera.yaw, camera.pitch);
        
        Log::info("FPS: {}", 1.0 / dt);

        float addition_time = 1 / FPS - dt;
        if (addition_time > 0.0f) {
            Core::Time::sleep(addition_time);
            dt = 1 / FPS;
        }
    }
}

Engine::Engine(std::string title)
        : window(std::move(title)), projectionMatrix(window.get_size_ref()) {
	window.init();

    renderer.init(glm::vec3(0.f, 1.f, 1.f));
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
    renderer.render(window, registry, *shader);
}

