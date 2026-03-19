#pragma once

#include <GLFW/glfw3.h>

class KeyboardControl {
private:
    GLFWwindow* window = nullptr;

public:
    KeyboardControl() = default;
    
    void setWindow(GLFWwindow* new_window) {
        window = new_window;
    }

    void update() {
	    wasPressF11 = isPressF11;
	    isPressF11 = glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS;

	    wasPressEcs = isPressEcs;
	    isPressEcs = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

	    wasPressA = isPressA;
	    isPressA = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;

	    wasPressW = isPressW;
	    isPressW = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;

	    wasPressS = isPressS;
	    isPressS = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;

	    wasPressD = isPressD;
		isPressD = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;

		wasPressB = isPressB;
		isPressB = glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS;

		wasPressN = isPressN;
		isPressN = glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS;

		wasPressLShift = isPressLShift;
		isPressLShift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

		wasPressRShift = isPressRShift;
		isPressRShift = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;

		wasPressSpace = isPressSpace;
		isPressSpace = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	}

	bool isPressedF11() { return isPressF11 && !wasPressF11; }

	bool isPressedEcs() { return isPressEcs && !wasPressEcs; }

	bool isPressedA() { return isPressA && !wasPressA; }
	bool isPressedMovementA() { return isPressA; }

	bool isPressedW() { return isPressW && !wasPressW; }
	bool isPressedMovementW() { return isPressW; }

	bool isPressedS() { return isPressS && !wasPressS; }
	bool isPressedMovementS() { return isPressS; }

	bool isPressedD() { return isPressD && !wasPressD; }
	bool isPressedMovementD() { return isPressD; }

	bool isPressedB() { return isPressB && !wasPressB; }
	bool isPressedMovementB() { return isPressB; }

	bool isPressedN() { return isPressN && !wasPressN; }
	bool isPressedMovementN() { return isPressN; }

	bool isPressedLShift() { return isPressLShift && !wasPressLShift; }
	bool isPressedMovementLShift() { return isPressLShift; }

	bool isPressedRShift() { return isPressRShift && !wasPressRShift; }
	bool isPressedMovementRShift() { return isPressRShift; }

	bool isPressedSpace() { return isPressSpace && !wasPressSpace; }
	bool isPressedMovementSpace() { return isPressSpace; }

private:
	bool isPressF11 = false;
	bool wasPressF11 = false;

	bool isPressEcs = false;
	bool wasPressEcs = false;

	bool isPressA = false;
	bool wasPressA = false;

	bool isPressW = false;
	bool wasPressW = false;

	bool isPressS = false;
	bool wasPressS = false;

	bool isPressD = false;
	bool wasPressD = false;
		
	bool isPressB = false;
	bool wasPressB = false;

	bool isPressN = false;
	bool wasPressN = false;

	bool isPressLShift = false;
	bool wasPressLShift = false;

	bool isPressRShift = false;
	bool wasPressRShift = false;

	bool isPressSpace = false;
	bool wasPressSpace = false;
};

