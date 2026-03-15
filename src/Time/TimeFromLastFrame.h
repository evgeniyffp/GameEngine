#pragma once

#include "./Timer.h"

class TimeFromLastFrame {
private:
    static Timer timer;

	static double deltaTime;
	static double currentTime;
	static double lastTime;

public:
	static void update() {
        deltaTime = timer.elapsed_seconds();
        timer.restart();
	}

	static double get() { return deltaTime; }
};

using deltaTime = TimeFromLastFrame;

