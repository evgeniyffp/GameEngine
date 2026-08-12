#pragma once

#include <string>

#include <glm/glm.hpp>

// must include glad and then glfw
#include <Engine/Utilities/Setting/Setting.h> // need for .cpp
#include <GLFW/glfw3.h>

#include <Engine/Core/InputControl/KeyboardControl.h>
#include <Engine/Core/InputControl/MouseControl.h>

class Window {
private:
	GLFWwindow* window;
    glm::ivec2 size;
	std::string title;

    KeyboardControl keyboard_control;
    MouseControl mouse_control;

    void initGLFW();
    void initWindow();

public:
	Window(std::string title);
	~Window();

    GLFWwindow* get();
    const GLFWwindow* get() const;

    glm::ivec2& get_size_ref();

    KeyboardControl& getKeyboardControl();
    MouseControl& getMouseControl();

    bool isClosed();
    void close();

    void init();

	void update();
};

