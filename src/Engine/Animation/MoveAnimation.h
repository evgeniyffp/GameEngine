#pragma once

#include "./Animation.h"

class MoveAnimation : public Animation {
private:
    vec3 final_position;

public:
    MoveAnimation(Transformable& target, float duration, std::unique_ptr<Easing> easing, vec3 final_position)
        : Animation(target, duration, std::move(easing)), final_position(final_position) {}

    ~MoveAnimation() override = default;

    void apply(float delta_percentage) {
        target.move(delta_percentage * final_position);
    }
};

