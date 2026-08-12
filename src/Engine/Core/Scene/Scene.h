#pragma once

#include <string>
#include <optional>

#include <entt/entt.hpp>

#include <Engine/ECS/Components/ModelComponent.h>
#include <Engine/ECS/Components/TransformComponent.h>

#include <Engine/Utilities/ModelImporter/ModelImporter.h>

class Scene {
private:
    entt::registry registry;

public:
    std::optional<entt::entity> addModel(std::string file_name) {
        auto entity = registry.create();

        ModelComponent model = ModelImporter::loadFull(file_name);
 
        if (model.parts.empty()) {
            Log::error("Failed to load model");
            return {};
        }

        model.file_name = std::move(file_name);

        registry.emplace<ModelComponent>(entity, std::move(model));
        registry.emplace<TransformComponent>(entity);

        return entity;
    }

    void clear() {
        registry.clear();
    }

    entt::registry& getRegistry() {
        return registry;
    }

    const entt::registry& getRegistry() const {
        return registry;
    }
};

