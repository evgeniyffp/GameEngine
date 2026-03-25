#include "Game.h"

#include <Engine/Easing/PowerEasing.h>

#include <Engine/Animation/MoveAnimation.h>
#include <Engine/Animation/ColorAnimation.h>

#include <Engine/Graphics/CameraController/BasicCameraController.h>
#include <Engine/Dron/Dron.h>

#include <Time/Time.h>

#include <utils/displayInfo.h>

void Game::updateCameras() {
	if (getKeyboardControl().isPressedOnce("N")) 
	++selectedCamera;
	if (selectedCamera >= cameras.size())
        selectedCamera = 0;
}

void Game::initUniforms() {
	updateUniforms();
	shaders[Shader_Core_Program].setUniformProjectionMatrix(projectionMatrix, "projectionMatrix");
}

void Game::updateUniforms() {
	shaders[Shader_Core_Program].setUniform_material(materials[0], "material0");

    shaders[Shader_Core_Program].setUniform_1i(lights.size(), "u_lights.count");
	for (int i = 0; i < lights.size(); ++i) {
        shaders[Shader_Core_Program].setUniform_light(lights[i], "u_lights.array[" + std::to_string(i) + "]");
	}

	shaders[Shader_Core_Program].setUniform_camera(cameraControllers[selectedCamera]->get(), "");
}

void Game::updateKeyboardInput() {
    auto dt = deltaTime::get();

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
		    cameraControllers[selectedCamera]->move_in_direction(direction, dt);
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

	shaders.emplace_back("shaders/vertex_core.glsl", "shaders/fragment_core.glsl");
	// lights.emplace_back(vec3(0.0f), 10.f, vec3(1.0f, 0.0f, 0.0f));

    textures.emplace_back("./Files/Images/Brick.png", GL_TEXTURE_2D);
	materials.emplace_back(vec3(1.0f), vec3(1.0f), vec3(0.0f));

	projectionMatrix.update();
	initModels();
	initUniforms();
}

void Game::initModels() {
	world.emplace_back(
		vec3(0.0f, 0.0f, -10.0f),
		materials[0],
        // "./Files/Objects/BigCity.obj",
        "./Files/Objects/Monkey.obj",
        textures[0]
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

void Game::update() {
	deltaTime::update();
    window.update();

    animation_manager.update(deltaTime::get());
    world.update();
	updateCameras();
	
    glm::vec3 vec(rand(), rand(), rand());
    vec = glm::normalize(vec);

	if (getMouseControl().isPressedOnce("LEFT"))
		lights.emplace_back(cameras[selectedCamera].getPosition(), .5f, vec);
		// lights[0].setPosition(cameras[selectedCamera].getPosition());
    
    cameraControllers[selectedCamera]->update(getMouseControl().getOffset(), deltaTime::get());
	
    updateKeyboardInput();
	updateUniforms();

    displayInfo(std::to_string(1.0 / deltaTime::get()));
}

