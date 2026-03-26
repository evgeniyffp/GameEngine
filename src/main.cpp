#include "Game/Game.h"

#include <utils/Log.h>

int main() {
	try {
        Log::init();

		Game game("Game Engine");
	
		game.loop();
	}
	catch (const std::string& error) {
	    Log::critical("EXXEPTION ERROR => {}", error);
	}

	return 0;
}

