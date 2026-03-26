#pragma once

#include <unordered_map>

#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

class MouseControl {
private:
    inline static const std::unordered_map<std::string, const int> keymap{
        { "LEFT" , GLFW_MOUSE_BUTTON_LEFT },
        { "RIGHT" , GLFW_MOUSE_BUTTON_RIGHT },
        { "MIDLE" , GLFW_MOUSE_BUTTON_MIDDLE }
    };

    std::unordered_map<std::string, bool> isPressButton;
    std::unordered_map<std::string, bool> wasPressButton;

    glm::dvec2 lastMouse = { 0.0, 0.0 };
    glm::dvec2 mouse = { 0.0, 0.0 };
    glm::dvec2 mouseOffset = { 0.0, 0.0 };
	bool firtsMouse = true;

    GLFWwindow* window = nullptr;

public:
    void setWindow(GLFWwindow* new_window) {
        window = new_window;
    }

    glm::dvec2 getOffset() const {
        return mouseOffset;
    }

    void update() {
	    wasPressButton = isPressButton;
        for (const auto& [keyname, key] : keymap)
	        isPressButton[keyname] = (glfwGetMouseButton(window, key) == GLFW_PRESS);
        
        glfwGetCursorPos(window, &mouse.x, &mouse.y);

    	if (firtsMouse) {
	    	lastMouse = mouse;
	    	firtsMouse = false;
	    }

	    mouseOffset = { mouse.x - lastMouse.x, lastMouse.y - mouse.y };

	    lastMouse = mouse;
    }

	bool isPressedOnce(const std::string& key) {
        return isPressButton[key] && !wasPressButton[key];
    }

	bool isPressed(const std::string& key) {
        return isPressButton[key];
    }
};

