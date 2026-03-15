#pragma once

#include "./Animation.h"

class MoveAnimation : public Animation {
private:
    vec3 final_position;

public:
    MoveAnimation(Transformable& target, float duration, vec3 final_position)
        : Animation(target, duration), final_position(final_position) {}
    
    float duration;
    float elapsed = 0.0f;
 
    void apply(float delta_percentage) {
        target.move(delta_percentage * final_position);
    }
};

