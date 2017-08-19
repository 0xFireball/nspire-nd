
#pragma once

#include "../deps.h"

#include "../entity/NBasic.h"
#include "NTween.h"

class NTweenParams {
private:
    std::function<void(NTweenParams &)> _finishCallback;
public:
    NTween tween;
    float duration;
    float age = 0;
    bool done = false;

    NTweenParams(NTween tw, float duration, std::function<void(NTweenParams &)> finishCallback = nullptr) : _finishCallback(finishCallback), tween(tw),
        duration(duration) {}

    bool update(float dt) {
        if (!done) {
            age += dt;
            if (age > duration) {
                age = duration;
                done = true;
            }
            tween.update(age / duration);
            return !done;
        } else {
            if (this->_finishCallback) {
                this->_finishCallback(*this);
            }
            return false;
        }
    }
};

class NTweenManager : public NBasic {
protected:
    std::vector<NTweenParams> tweens;
public:
    virtual void update(float dt);

    
};
