#pragma once

#include <string>

#include <glm/glm.hpp>
using namespace glm;

// must include glad and then glfw
#include <Engine/Utilities/Setting/Setting.h> // need for .cpp
#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow* window;
	ivec2 size;
	std::string title;

    void initGLFW();
    void initWindow();

public:
	Window(std::string title);
	~Window();

    GLFWwindow* get();

    ivec2& get_size_ref();

    bool is_closed();
    void close();

    void init();

	void update();
};

