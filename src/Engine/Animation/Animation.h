#pragma once

#include <memory>

#include <Engine/Easing/Easing.h>

class Animation {
private:
    float duration;
    float elapsed = 0.0f;
    bool finished = false;
    std::unique_ptr<Easing> easing;

public:
    Animation(float duration, std::unique_ptr<Easing> easing)
        : duration(duration), easing(std::move(easing)) {}

    Animation(Animation&& other) = default;

    virtual ~Animation() = default;

    void update(float dt) {
        if (finished)
            return;

        float old_progres = elapsed / duration;

        elapsed += dt;

        if (elapsed >= duration) {
            elapsed = duration;
            finished = true;
        }
        
        float new_progres = elapsed / duration;

        float delta_percentage = easing->ease(new_progres) - easing->ease(old_progres);

        apply(delta_percentage);
    }

    virtual void apply(float delta_percentage) = 0;
    
    bool isFinished() const {
        return finished;
    }
};

