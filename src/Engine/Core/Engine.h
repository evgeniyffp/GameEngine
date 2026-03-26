#pragma once

#include <vector>
#include <deque>

#include <memory>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <Engine/Camera/Camera.h>
#include <Engine/Camera/CameraController.h>

#include <Engine/Wordl/Wordl.h>
#include <Engine/Utilities/ProjectionMatrix/ProjectionMatrix.h>

#include <Engine/Animation/AnimationManager.h>

#include <Time/Profiler.h>

#include "./Window/Window.h"

enum shaderEnum { Shader_Core_Program = 0 };

class Engine {
private:
    bool isInitGLAD = false;
	void initGLAD();
	
    std::vector<Shader> shaders;

    void initUniforms();
    void updateUniforms();

protected:
    float FPS = 60.0f;

    Window window;
	
	World world;

	ProjectionMatrix projectionMatrix;

	std::vector<Light> lights;

	std::vector<Material> materials;
	
    int selectedCameraController = 0;
	std::deque<Camera> cameras;
	std::vector<std::unique_ptr<CameraController>> cameraControllers;

    std::vector<Texture> textures;

    AnimationManager animation_manager;

    void addShader(const std::string& vertex_filename, const std::string& fragment_filename);

public:
	void loop();
	
	Engine(std::string title);
    virtual ~Engine() = default;

    KeyboardControl& getKeyboardControl() {
        return window.getKeyboardControl();
    }

    MouseControl& getMouseControl() {
        return window.getMouseControl();
    }

    void close() {
        window.close();
    }

	virtual void update(float dt) = 0;
	void render();
};

