#pragma once

#include "./Easing.h"

template <unsigned int Power>
class InPowerEasing : public Easing {
public:
    ~InPowerEasing() override = default;

    float ease(float progress) const override {
        return std::pow(progress, Power);
    }
};

using LinearEasing = InPowerEasing<1>;
using InQuadraticEasing = InPowerEasing<2>;
using InCubicEasing = InPowerEasing<3>;

template <unsigned int Power>
class OutPowerEasing : public Easing {
public:
    ~OutPowerEasing() override = default;
    
    float ease(float progress) const override {
        return 1.0f - std::pow(1.0f - progress, Power);
    }
};

using OutQuadraticEasing = OutPowerEasing<2>;
using OutCubicEasing = OutPowerEasing<3>;

template <unsigned int Power>
class InOutPowerEasing : public Easing {
public:
    ~InOutPowerEasing() override = default;
    
    float ease(float progress) const override {
        if (progress < 0.5f)
            return std::pow(progress * 2.0f, Power) / 2.0f;
        else
            return 1.0f - std::pow(2.0f - progress * 2.0f, Power) / 2.0f;
    }
};

