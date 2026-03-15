#pragma once

#include <vector>

#include <Engine/Graphics/Model/Model.h>

class World {
private:
	std::vector<Model> models;

public:
    template <typename... Args>
    void emplace_back(Args&&... args) {
        models.emplace_back(std::forward<Args>(args)...);
    }

	void push_back(Model addedModel);

    void update();
	void render(const Shader& shader) const;

	Model& operator[](size_t index);
};

