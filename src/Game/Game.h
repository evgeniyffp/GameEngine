#pragma once

#include <Engine/Core/Engine.h>

class Game final : public Engine {
private:
	void initModels();

	void initUniforms();
	void updateUniforms();

	void updateCameras();

	int selectedCamera = 0;

	void updateMouseInput();
	void updateKeyboardInput();

public:
	Game(std::string title);
    ~Game() override = default;

	void update() override;
};

