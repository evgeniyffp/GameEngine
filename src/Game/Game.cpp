#include "Game.h"

#include <Time/Time.h>

#include <Engine/Events/Events.h>
#include <Engine/Events/Keyboard.h>

#include <utils/displayInfo.h>

void Game::updateCameras() {
	if (Core::Events::Keyboard::isPressedN()) 
		++selectedCamera;
	if (selectedCamera >= cameras.size())
        selectedCamera = 0;
}

void Game::initUniforms() {
	updateUniforms();
	shaders[Shader_Core_Program].setUniformProjectionMatrix(projectionMatrix, "protectionMatrix");
}

void Game::updateUniforms() {
	shaders[Shader_Core_Program].setUniform_material(materials[0], "material0");

	for (const auto& light : lights) {
		shaders[Shader_Core_Program].setUniform_light(light, "light0");
	}
	shaders[Shader_Core_Program].setUniform_camera(cameras[selectedCamera], "");
}

void Game::updateKeyboardInput() {
	if (Core::Events::Keyboard::isPressedMovementW())
		cameras[selectedCamera].move_in_direction(Direction::Forward);
	if (Core::Events::Keyboard::isPressedMovementS())
		cameras[selectedCamera].move_in_direction(Direction::Backward);

	if (Core::Events::Keyboard::isPressedMovementD())
		cameras[selectedCamera].move_in_direction(Direction::Right);
	if (Core::Events::Keyboard::isPressedMovementA())
		cameras[selectedCamera].move_in_direction(Direction::Left);

	if (Core::Events::Keyboard::isPressedMovementLShift())
		cameras[selectedCamera].move_in_direction(Direction::Up);
	if (Core::Events::Keyboard::isPressedMovementSpace())
		cameras[selectedCamera].move_in_direction(Direction::Down);

    vec3 rotation(0.0f);
	if (glfwGetKey(window.get(), GLFW_KEY_K) == GLFW_PRESS)
		rotation.y -= 1.0f;
	if (glfwGetKey(window.get(), GLFW_KEY_L) == GLFW_PRESS)
		rotation.y += 1.0f;
	world[0].rotate(rotation);

	if (Core::Events::Keyboard::isPressedB())
		GLSetting::changeRenderMode();
	
    if (Core::Events::Keyboard::isPressedEcs())
        window.close();
}

Game::Game(std::string title) : Engine::Engine(title) {
	cameras.emplace_back(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
        5
	);
    cameras.emplace_back(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
        20
	);
	cameras.emplace_back(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
        100
	);

	shaders.emplace_back("shaders/vertex_core.glsl", "shaders/fragment_core.glsl");
	lights.emplace_back(vec3(0.0f), 0.5f);
    
    textures.emplace_back("./Files/Images/Brick.png", GL_TEXTURE_2D);
	materials.emplace_back(vec3(1.0f), vec3(1.0f), vec3(0.0f), true);

	projectionMatrix.update();
	initModels();
	initUniforms();
}

#include <Engine/Animation/MoveAnimation.h>

void Game::initModels() {
	world.emplace_back(
		vec3(0.0f, 0.0f, -3.0f),
		materials[0],
        "./Files/Objects/Monkey.obj",
        textures[0]
    );

    animation_manager.emplace<MoveAnimation>(
        world[0],
        5.f,
        std::make_unique<PowerEasing<1>>(),
        vec3(-10, 0, 0)
    );
}

void Game::update() {
    window.update();
	deltaTime::update();

    animation_manager.update(deltaTime::get());
    world.update();
	updateCameras();
	
	if (glfwGetMouseButton(window.get(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
		lights[0].setPosition(cameras[selectedCamera].getPosition());
    cameras[selectedCamera].update(mouse_control.getOffset());
	mouse_control.update();
	
    updateKeyboardInput();
	updateUniforms();

    displayInfo(std::to_string(1.0 / deltaTime::get()));
/*
	std::cout << cameras[selectedCamera].position.x << ' '
			  << cameras[selectedCamera].position.y << ' '
			  << cameras[selectedCamera].position.z << std::endl;
*/
}

