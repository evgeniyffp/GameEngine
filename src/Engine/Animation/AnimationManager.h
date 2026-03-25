#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "./Animation.h"

class AnimationManager {
private:
    std::vector<std::unique_ptr<Animation>> animations;

public:
    void add(std::unique_ptr<Animation> animation) {
        animations.push_back(std::move(animation));
    }
    
    template <typename AnimationT, typename... Args>
    void emplace(Args&&... args) {
        animations.push_back(std::make_unique<AnimationT>(std::forward<Args>(args)...));
    }
    
    void update(float dt) {
        for (auto& i : animations) {
            i->update(dt);
        }
    
        auto l = [](const auto& a) {
            return a->isFinished(); 
        };

        animations.erase(std::remove_if(animations.begin(), animations.end(), l), animations.end());
    }
};
