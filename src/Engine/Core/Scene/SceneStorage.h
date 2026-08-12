#pragma once

#include <unordered_map>
#include <functional>

#include "./Scene.h"

class SceneStorage {
public:
    using tag_t = std::string;
    using data_t = std::unordered_map<tag_t, Scene>;

private:
    data_t scenes;

public:
    Scene& get(const tag_t& tag) {
        return scenes[tag];
    }

    void for_each(const std::function<void(const tag_t&, Scene&)>& f) {
        for (auto& [tag, scene] : scenes) {
            f(tag, scene);
        }
    }

    void for_each(const std::function<void(const tag_t&, const Scene&)>& f) const {
        for (auto& [tag, scene] : scenes) {
            f(tag, scene);
        }
    }
};

