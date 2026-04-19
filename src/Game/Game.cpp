#include "./Game.h"

#include <Engine/ECS/Components/MaterialComponent.h>
#include <Engine/ECS/Components/MeshComponent.h>
#include <Engine/ECS/Components/TransformComponent.h>
#include <Engine/ECS/Components/LightComponent.h>
#include <Engine/ECS/Components/CameraComponent.h>

#include <Engine/ECS/Systems/CameraSystem.h>

#include <Engine/Utilities/ModelImporter/ModelImporter.h>

#include <Time/Time.h>

#include <utils/Log.h>

void Game::updateKeyboardInput(float dt) {
    std::unordered_map<std::string, Direction> key_to_direction = {
        { "W", Direction::Forward },
        { "A", Direction::Left },
        { "S", Direction::Backward },
        { "D", Direction::Right },
        { "LEFT_SHIFT", Direction::Down },
        { "SPACE", Direction::Up }
    };

    for (const auto& [key, direction] : key_to_direction) {
        if (getKeyboardControl().isPressed(key))
		    CameraSystem::move_in_direction(registry, active_camera, direction, dt);
    }

	if (getKeyboardControl().isPressedOnce("B"))
		GLSetting::changeRenderMode();
	
    if (getKeyboardControl().isPressedOnce("ESC"))
        close();
}

Game::Game(std::string title) : Engine::Engine(std::move(title)) {
	setShader("shaders/vertex_core.glsl", "shaders/fragment_core.glsl");
    
    active_camera = registry.create();
    registry.emplace<CameraComponent>(active_camera, 
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
    );

    // std::string object_file = "./Files/Objects/Monkey.obj";
    // std::string object_file = "./Files/Objects/BigCity.obj";
    // std::string object_file = "./Files/Objects/bugatti/bugatti.blend";
    // std::string object_file = "./Files/Objects/very_big_city/Castelia City.obj";
    std::string object_file = "./Files/Objects/iron_man/IronMan.obj";
    // std::string object_file = "./Files/Objects/living_room/InteriorTest.blend";
    
    LoadedModel model = ModelImporter::loadFull(object_file);
    if (model.meshes.empty()) {
        Log::error("Failed to load model");
        return;
    }

    for (size_t i = 0; i < model.meshes.size(); ++i) {
        auto entity = registry.create();
        registry.emplace<TransformComponent>(entity);
        registry.emplace<MeshComponent>(entity, std::move(model.meshes[i]));
        registry.emplace<MaterialComponent>(entity, model.materials[i]);
    }
}

void Game::update(float dt) {
	if (getMouseControl().isPressedOnce("LEFT")) {
        auto light = registry.create();

        const auto position = registry.get<CameraComponent>(active_camera).position;
	    registry.emplace<TransformComponent>(light, PositionComponent{position});

        const auto random_color = glm::normalize(glm::vec3(rand(), rand(), rand()));
	    registry.emplace<LightComponent>(light, 20.f, glm::vec3(1.f));
    }
    
    updateKeyboardInput(dt);
}

