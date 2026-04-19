#pragma once

#include <memory>
#include <vector>
#include <deque>

#include <entt/entt.hpp>

#include <Engine/Shader/Shader.h>
#include <Engine/Utilities/ProjectionMatrix/ProjectionMatrix.h>

#include "./Window/Window.h"
#include "./Renderer/Renderer.h"

class Engine {
private:
    float FPS = 60000.0f;
    Window window;

    Renderer renderer;

    ProjectionMatrix projectionMatrix;
    
    void initUniforms();
    
    std::unique_ptr<Shader> shader;

protected:
    entt::registry registry;
    entt::entity active_camera;

    void setShader(const std::string& vertex_filename, const std::string& fragment_filename);

public:
	void loop();
	
	Engine(std::string title);
    virtual ~Engine() = default;

    KeyboardControl& getKeyboardControl();

    MouseControl& getMouseControl();

    void close();

	virtual void update(float dt) = 0;
	void render();
};

