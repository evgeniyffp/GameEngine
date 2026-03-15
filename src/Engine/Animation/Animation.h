#pragma once

class Animation {
protected:
    Transformable& target;
    float duration;
    float elapsed = 0.0f;
    bool finished = false;

public:
    Animation(Transformable& target, float duration)
        : target(target), duration(duration) {}
    
    virtual ~Animation() = default;

    // TODO добавить easing-функции: квадратичная, синусоидная, кривую Безье
    // сейчас используется линейная
    void update(float dt) {
        if (finished)
            return;

        float old_elapsed = elapsed;

        elapsed += dt;

        if (elapsed >= duration) {
            elapsed = duration;
            finished = true;
        }

        apply((elapsed - old_elapsed) / duration);
    }

    virtual void apply(float delta_percentage) = 0;
    
    bool isFinished() const {
        return finished;
    }
};

