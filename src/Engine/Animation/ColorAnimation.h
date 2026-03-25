#pragma once

#include "./Animation.h"

#include <Engine/Interfaces/Colorable.h>

class ColorAnimation : public Animation {
public:
    enum class Types {
        Absolute,
        Relative
    };

private:
    Colorable& target;
    vec3 delta_color;

    vec3 calculate_delta_color(vec3 color, Types type) {
        switch (type) {
            case Types::Absolute:
                return color - target.getColor();
            case Types::Relative:
                return color;
        };
        return {};
    }

public:
    ColorAnimation(Colorable& target, float duration, std::unique_ptr<Easing> easing, vec3 color, Types type)
        : Animation(duration, std::move(easing)), target(target)
        , delta_color(calculate_delta_color(color, type)) {}

    ~ColorAnimation() override = default;

    void apply(float delta_percentage) override {
        target.doColor(delta_percentage * delta_color);
    }
};

