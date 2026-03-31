#include "./Game.h"

#include <Engine/Animation/Easing/PowerEasing.h>
#include <Engine/Animation/MoveAnimation.h>
#include <Engine/Animation/ColorAnimation.h>

#include <Engine/Camera/BasicCameraController/BasicCameraController.h>
#include <Engine/Camera/Dron/Dron.h>

#include <Time/Time.h>

#include <utils/Log.h>

void Game::updateCameras() {
	if (getKeyboardControl().isPressedOnce("N")) 
	    ++selectedCameraController;
	selectedCameraController %= cameraControllers.size();
}

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
		    cameraControllers[selectedCameraController]->move_in_direction(direction, dt);
    }
/*
    vec3 rotation(0.0f);
	if (getKeyboardControl().isPressed("K"))
		rotation.y -= 1.0f;
	if (getKeyboardControl().isPressed("L"))
		rotation.y += 1.0f;
	world[0].rotate(rotation);
*/
	if (getKeyboardControl().isPressedOnce("B"))
		GLSetting::changeRenderMode();
	
    if (getKeyboardControl().isPressedOnce("ESC"))
        close();
}

Game::Game(std::string title) : Engine::Engine(title) {
	cameras.emplace_back(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f)
	);
    cameras.emplace_back(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f)
	);
	cameras.emplace_back(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f)
	);

    cameraControllers.push_back(std::make_unique<BasicCameraController>(cameras[0], 10));
    cameraControllers.push_back(std::make_unique<BasicCameraController>(cameras[1], 50));
    cameraControllers.push_back(std::make_unique<Dron>(cameras[2], 100));

	addShader("shaders/vertex_core.glsl", "shaders/fragment_core.glsl");
	// lights.emplace_back(vec3(0.0f), 10.f, vec3(1.0f, 0.0f, 0.0f));

    Texture texture("./Files/Images/Brick.png", GL_TEXTURE_2D);
	Material material(vec3(1.0f), vec3(1.0f), vec3(0.0f));
    material.setDiffuseTexture(std::move(texture));

    materials.push_back(std::move(material));

	projectionMatrix.update();
	initModels();
}

void Game::initModels() {
	world.emplace_back(
		vec3(0.0f, 0.0f, -10.0f),
		materials[0],
        //  "./Files/Objects/BigCity.obj",
        "./Files/Objects/Monkey.obj"
    );

/*
    animation_manager.emplace<MoveAnimation>(
        world[0],
        10.f,
        std::make_unique<InOutPowerEasing<4>>(),
        vec3(-70.0, 0, 0),
        MoveAnimation::Types::Relative
    );

    animation_manager.emplace<ColorAnimation>(
        materials[0],
        5.f,
        std::make_unique<InOutPowerEasing<3>>(),
        vec3(0.1f, 0.1f, 1.0f),
        ColorAnimation::Types::Absolute
    );
*/
}

void Game::update(float dt) {
    window.update();

    animation_manager.update(dt);
    world.update();
	updateCameras();
	
    glm::vec3 vec(rand(), rand(), rand());
    vec = glm::normalize(vec);

	if (getMouseControl().isPressedOnce("LEFT"))
		lights.emplace_back(cameras[selectedCameraController].getPosition(), .5f, vec);

    cameraControllers[selectedCameraController]->update(getMouseControl().getOffset(), dt);
	
    updateKeyboardInput(dt);

    Log::info("FPS: {}", 1.0 / dt);
}

