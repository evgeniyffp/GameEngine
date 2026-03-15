#include "Game/Game.h"

#include <utils/displayInfo.h>

int main() {
	try {
		Game game("Game Engine");
		
		game.loop();
	}
	catch (const std::string& error) {
		displayInfo("EXXEPTION ERROR => " + error);
	}

	return 0;
}

