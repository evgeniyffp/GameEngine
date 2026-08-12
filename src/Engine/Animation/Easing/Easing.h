#pragma once

class Easing {
public:
    virtual ~Easing() = default;
   
    // return and progress - [0; 1]
    virtual float ease(float progress) const = 0;
};

