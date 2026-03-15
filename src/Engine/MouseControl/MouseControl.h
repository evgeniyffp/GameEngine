#pragma once

#include <GLFW/glfw3.h>

class MouseControl {
private:
	dvec2 lastMouse = { 0.0, 0.0 };
	dvec2 mouse = { 0.0, 0.0};
	dvec2 mouseOffset = { 0.0, 0.0 };
	bool firtsMouse = true;

    GLFWwindow* window = nullptr;

public:
    void setWindow(GLFWwindow* new_window) {
        window = new_window;
    }

    dvec2 getOffset() const {
        return mouseOffset;
    }

    void update() {
	    glfwGetCursorPos(window, &mouse.x, &mouse.y);

    	if (firtsMouse) {
	    	lastMouse = mouse;
	    	firtsMouse = false;
	    }

	    mouseOffset = { mouse.x - lastMouse.x, lastMouse.y - mouse.y };

	    lastMouse = mouse;
    }
};
