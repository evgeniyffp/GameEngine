#pragma once

#include <Engine/Core/Engine.h>

class Game final : public Engine {
private:
	void initModels();

	void initUniforms();
	void updateUniforms();

	void updateCameras();

public:
	Game(std::string title);
    ~Game() override = default;

	void update(float dt) override;
};

