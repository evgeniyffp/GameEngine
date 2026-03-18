#include "Game/Game.h"

#include <utils/displayInfo.h>

#include <iostream>

int main() {
	try {
		Game game("Game Engine");
	
        // glfwSwapInterval(0); // remove VSycs

		game.loop();
	}
	catch (const std::string& error) {
		displayInfo("EXXEPTION ERROR => " + error);
	}

	return 0;
}

