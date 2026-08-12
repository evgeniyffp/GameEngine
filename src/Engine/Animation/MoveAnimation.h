#pragma once

#include "./Animation.h"

#include <Engine/Interfaces/Movable.h>

class MoveAnimation : public Animation {
public:
    enum class Type {
        Absolute,
        Relative
    };

private:
    Movable& target;
    vec3 delta_position;

    vec3 calculate_delta_position(vec3 position, Types type) {
        switch (type) {
            case Types::Absolute:
                return position - target.getPosition();
            case Types::Relative:
                return position;
        };
        return {};
    }

public:
    MoveAnimation(Movable& target, float duration, std::unique_ptr<Easing> easing, vec3 position, Type type)
        : Animation(duration, std::move(easing)), target(target)
        , delta_position(calculate_delta_position(position, type)) {}

    ~MoveAnimation() override = default;

    void apply(float delta_percentage) override {
        target.move(delta_percentage * delta_position);
    }
};

