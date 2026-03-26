#pragma once

#include <unordered_map>

#include <GLFW/glfw3.h>

class KeyboardControl {
private:
    inline static const std::unordered_map<std::string, const int> keymap{
        { "A", GLFW_KEY_A },
        { "B", GLFW_KEY_B },
        { "C", GLFW_KEY_C },
        { "D", GLFW_KEY_D },
        { "E", GLFW_KEY_E },
        { "G", GLFW_KEY_G },
        { "H", GLFW_KEY_H },
        { "I", GLFW_KEY_I },
        { "J", GLFW_KEY_J },
        { "K", GLFW_KEY_K },
        { "L", GLFW_KEY_L },
        { "M", GLFW_KEY_M },
        { "N", GLFW_KEY_N },
        { "O", GLFW_KEY_O },
        { "P", GLFW_KEY_P },
        { "Q", GLFW_KEY_Q },
        { "R", GLFW_KEY_R },
        { "S", GLFW_KEY_S },
        { "T", GLFW_KEY_T },
        { "U", GLFW_KEY_U },
        { "V", GLFW_KEY_V },
        { "W", GLFW_KEY_W },
        { "X", GLFW_KEY_X },
        { "Y", GLFW_KEY_Y },
        { "Z", GLFW_KEY_Z },
        { "F1", GLFW_KEY_F1 },
        { "F2", GLFW_KEY_F2 },
        { "F3", GLFW_KEY_F3 },
        { "F4", GLFW_KEY_F4 },
        { "F5", GLFW_KEY_F5 },
        { "F6", GLFW_KEY_F6 },
        { "F7", GLFW_KEY_F7 },
        { "F8", GLFW_KEY_F8 },
        { "F9", GLFW_KEY_F9 },
        { "F10", GLFW_KEY_F10 },
        { "F11", GLFW_KEY_F11 },
        { "F12", GLFW_KEY_F12 },
        { "LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT },
        { "RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT },
        { "ESC", GLFW_KEY_ESCAPE },
        { "SPACE", GLFW_KEY_SPACE }
    };

    GLFWwindow* window = nullptr;

public:
    KeyboardControl() = default;
    
    void setWindow(GLFWwindow* new_window) {
        isPressButton.clear();
        wasPressButton.clear();

        window = new_window;
    }

    void update() {
        wasPressButton = isPressButton;
        for (const auto& [keyname, key] : keymap) {
	        isPressButton[keyname] = (glfwGetKey(window, key) == GLFW_PRESS);
        }
	}

	bool isPressedOnce(const std::string& key) {
        return isPressButton[key] && !wasPressButton[key];
    }

	bool isPressed(const std::string& key) {
        return isPressButton[key];
    }

private:
    std::unordered_map<std::string, bool> isPressButton;
    std::unordered_map<std::string, bool> wasPressButton;
};

