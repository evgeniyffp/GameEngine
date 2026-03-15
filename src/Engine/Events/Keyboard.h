#pragma once

#include <GLFW/glfw3.h>

namespace Core::Events {
	class Keyboard {
	public:
		static void update(GLFWwindow* window) {
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

		static bool isPressedF11() { return isPressF11 && !wasPressF11; }

		static bool isPressedEcs() { return isPressEcs && !wasPressEcs; }

		static bool isPressedA() { return isPressA && !wasPressA; }
		static bool isPressedMovementA() { return isPressA; }

		static bool isPressedW() { return isPressW && !wasPressW; }
		static bool isPressedMovementW() { return isPressW; }

		static bool isPressedS() { return isPressS && !wasPressS; }
		static bool isPressedMovementS() { return isPressS; }

		static bool isPressedD() { return isPressD && !wasPressD; }
		static bool isPressedMovementD() { return isPressD; }

		static bool isPressedB() { return isPressB && !wasPressB; }
		static bool isPressedMovementB() { return isPressB; }

		static bool isPressedN() { return isPressN && !wasPressN; }
		static bool isPressedMovementN() { return isPressN; }

		static bool isPressedLShift() { return isPressLShift && !wasPressLShift; }
		static bool isPressedMovementLShift() { return isPressLShift; }

		static bool isPressedRShift() { return isPressRShift && !wasPressRShift; }
		static bool isPressedMovementRShift() { return isPressRShift; }

		static bool isPressedSpace() { return isPressSpace && !wasPressSpace; }
		static bool isPressedMovementSpace() { return isPressSpace; }


	private:
		static bool isPressF11;
		static bool wasPressF11;

		static bool isPressEcs;
		static bool wasPressEcs;

		static bool isPressA;
		static bool wasPressA;

		static bool isPressW;
		static bool wasPressW;

		static bool isPressS;
		static bool wasPressS;

		static bool isPressD;
		static bool wasPressD;
		
		static bool isPressB;
		static bool wasPressB;

		static bool isPressN;
		static bool wasPressN;

		static bool isPressLShift;
		static bool wasPressLShift;

		static bool isPressRShift;
		static bool wasPressRShift;

		static bool isPressSpace;
		static bool wasPressSpace;
	};
}

