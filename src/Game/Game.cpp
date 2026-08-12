#include "./Game.h"

#include <Engine/ECS/Components/TransformComponent.h>
#include <Engine/ECS/Components/LightComponent.h>

#include <Engine/ECS/Systems/CameraSystem.h>
#include <Engine/ECS/Systems/CameraControllerSystem.h>

#include <Engine/CameraController/BasicCameraController.h>

#include <Time/Time.h>

#include <utils/Log.h>

entt::entity createLight(entt::registry& registry, const glm::vec3& position, float light_intensity, const glm::vec3& color = glm::vec3(1.f)) {
    auto light = registry.create();

	registry.emplace<TransformComponent>(light, PositionComponent{position});
	registry.emplace<LightComponent>(light, light_intensity, color);

    return light;
}

Game::Game(std::string title) : Engine::Engine(std::move(title)) {
	setShader("shaders/vertex_core.glsl", "shaders/fragment_core.glsl");

    auto& main_registry = main_scene.getRegistry();

    active_camera = main_registry.create();
    main_registry.emplace<TransformComponent>(active_camera, 
		PositionComponent{glm::vec3(0.0f, 5.0f, 5.0f)}
    );
    main_registry.emplace<CameraComponent>(active_camera, 
		glm::vec3(0.0f, 1.0f, 0.0f),
        -30.f
    );
    main_registry.emplace<CameraControllerComponent>(active_camera, 
        std::make_unique<BasicCameraController>()
    );

    // std::string object_file = "./Files/Objects/BigCity.obj";
    // std::string object_file = "./Files/Objects/bugatti/bugatti.blend";
    // std::string object_file = "./Files/Objects/very_big_city/Castelia City.obj";
    // std::string object_file = "./Files/Objects/living_room/InteriorTest.blend";
    main_scene.addModel("./Files/Objects/iron_man/IronMan.obj");

    main_scene.addModel("./Files/plane.obj");
    main_scene.addModel("./Files/Objects/Monkey.obj");

    createLight(main_registry, glm::vec3(0.f, 50.f, 0.f), 20.f);
}

void Game::update(float dt) {
    auto& keyboard_control = getKeyboardControl();
    auto& mouse_control = getMouseControl();

/*
	if (mouse_control.isPressedOnce("LEFT")) {
        // const auto random_color = glm::normalize(glm::vec3(rand(), rand(), rand()));
        const auto position = registry.get<CameraComponent>(active_camera).position;
        create_light(registry, position, 20.f);
    }
*/

    if (keyboard_control.isPressedOnce("B"))
		GLSetting::changeRenderMode();
	
    if (keyboard_control.isPressedOnce("ESC"))
        close();

    CameraControllerSystem::update(main_scene.getRegistry(), active_camera, keyboard_control, mouse_control, dt);
}

