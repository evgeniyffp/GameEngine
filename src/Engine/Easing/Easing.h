#pragma once

class Easing {
public:
    virtual ~Easing() = default;
    
    // return and progress - [0; 1]
    virtual float ease(float progress) const = 0;
};

template <unsigned int Power>
class PowerEasing : public Easing {
public:
    ~PowerEasing() override = default;

    float ease(float progress) const override {
        return std::pow(progress, Power);
    }
};

using LinearEasing = PowerEasing<1>;
using QuadraticEasing = PowerEasing<2>;
using Cubic = PowerEasing<3>;

