#include "./Events.h"

#include "Keyboard.h"

namespace Core::Events {
	void update(GLFWwindow* window) {
		glfwPollEvents();
		Keyboard::update(window);
	}
}

