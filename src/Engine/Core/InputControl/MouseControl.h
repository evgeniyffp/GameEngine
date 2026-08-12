#pragma once

#include <unordered_map>

#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include <utils/Log.h>

class MouseControl {
private:
    inline static const std::unordered_map<std::string, const int> keymap{
        { "LEFT" , GLFW_MOUSE_BUTTON_LEFT },
        { "RIGHT" , GLFW_MOUSE_BUTTON_RIGHT },
        { "MIDLE" , GLFW_MOUSE_BUTTON_MIDDLE }
    };

    std::unordered_map<std::string, bool> isPressButton;
    std::unordered_map<std::string, bool> wasPressButton;

    glm::vec2 lastMouse = { 0.0, 0.0 };
    glm::vec2 mouse = { 0.0, 0.0 };
    glm::vec2 mouseOffset = { 0.0, 0.0 };
	bool firtsMouse = true;

    GLFWwindow* window = nullptr;

public:
    void setWindow(GLFWwindow* new_window) {
        window = new_window;
    }

    glm::vec2 getOffset() const {
        return mouseOffset;
    }

    void update() {
	    wasPressButton = isPressButton;
        for (const auto& [keyname, key] : keymap)
	        isPressButton[keyname] = (glfwGetMouseButton(window, key) == GLFW_PRESS);

        glm::dvec2 dmouse;   
        glfwGetCursorPos(window, &dmouse.x, &dmouse.y);
        mouse = dmouse;

    	if (firtsMouse) {
	    	lastMouse = mouse;
	    	firtsMouse = false;
	    }

	    mouseOffset = mouse - lastMouse;
        mouseOffset.y *= -1;

	    lastMouse = mouse;
    }

	bool isPressedOnce(const std::string& key) {
        return isPressButton[key] && !wasPressButton[key];
    }

	bool isPressed(const std::string& key) {
        return isPressButton[key];
    }
};

