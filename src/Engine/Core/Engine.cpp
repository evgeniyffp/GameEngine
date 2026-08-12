#include "Engine.h"

#include <Engine/ECS/Systems/LightSystem.h>
#include <Engine/ECS/Systems/CameraSystem.h>

#include <Engine/ECS/Components/TransformComponent.h>

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
    auto& main_registry = main_scene.getRegistry();

	while (!window.isClosed()) {
        Profiler profiler;

        {
            Profiler::Node _node(profiler, "frame");

            {
                Profiler::Node _node(profiler, "window.update()");
                window.update();
            }

            {
                Profiler::Node _node(profiler, "update()");
                update(dt);
            }

            {
                Profiler::Node _node(profiler, "<all ECS systems \\ RenderSystem>::update(...)");
                
                auto f = [&](const std::string&, Scene& scene) {
                    LightSystem::update(scene.getRegistry(), *shader);
                };
                
                scenes.for_each(f);
                CameraSystem::update(main_registry, active_camera, *shader);
            }

            {
                Profiler::Node _node(profiler, "render()");
                render();
            }

            {
                Profiler::Node _node(profiler, "sleep time");
                
                profiler.end("frame");
                dt = profiler.get("frame");

                float addition_time = 1 / FPS - dt;
                if (addition_time > 0.0f) {
                    Core::Time::sleep(addition_time);
                }
            }
                profiler.end("frame");
        }

        dt = profiler.get("frame");

        auto& data = profiler.get();

        Log::debug("{}", profiler.get(""));
        for (auto&& [name, time_interval] : data) {
            float elapsed = time_interval.elapsed_seconds();
            float perc = elapsed / dt * 100;
            Log::debug("* {}:\t{}ms,\t{}%", name, elapsed * 1000, perc);
       }

        const auto& camera = main_registry.get<CameraComponent>(active_camera);

        glm::vec3 camera_pos = main_registry.get<TransformComponent>(active_camera).position_component.position;
        Log::debug("Selected camera position - x:{}, y:{}, z:{}", camera_pos.x, camera_pos.y, camera_pos.z);

        Log::debug("Selected camera rotation - yaw:{}, pitch:{}", camera.yaw, camera.pitch);

        Log::info("FPS: {}", 1.0 / dt);
        Log::debug("{}", profiler.get(""));
    }
}

Engine::Engine(std::string title)
        : window(std::move(title)), projectionMatrix(window.get_size_ref()), main_scene(scenes.get("main_scene")) {
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
    renderer.render(window, scenes, *shader);
}

