#pragma once

#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <Engine/Wordl/Wordl.h>
#include <Engine/Utilities/ProjectionMatrix/ProjectionMatrix.h>

#include <Engine/Animation/AnimationManager.h>

#include <Time/TimeFromLastFrame.h>

#include <Engine/MouseControl/MouseControl.h>

#include "./Window.h"

enum shaderEnum { Shader_Core_Program = 0 };

class Engine {
protected:
    Window window;
	
    MouseControl mouse_control;

    bool isInitGLAD = false;
	void initGLAD();

	World world;

	ProjectionMatrix projectionMatrix;

	std::vector<Shader> shaders;

	std::vector<Light> lights;

	std::vector<Material> materials;

	std::vector<Camera> cameras;

    std::vector<Texture> textures;

    AnimationManager animation_manager;

public:
	void loop();
	
	Engine(std::string title);
	~Engine();

	virtual void update() = 0;
	void render();
};

