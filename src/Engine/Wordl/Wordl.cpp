#include "./Wordl.h"

void World::push_back(Model addedModel) {
	models.push_back(std::move(addedModel));
}

void World::update() {
    for (auto& i : models)
        i.update();
}

void World::render(const Shader& shader) const {
	for (const auto& i : models)
		i.render(shader);
}

Model& World::operator[](size_t index) {
	return models[index];
}

