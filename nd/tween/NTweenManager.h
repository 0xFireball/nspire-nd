
#pragma once

#include "../deps.h"

#include "../entity/NBasic.h"
#include "NTween.h"

class NTweenParams;
typedef std::function<void(NTweenParams &)> TweenCallback;

class NTweenParams {
private:
    TweenCallback _finishCallback;
public:
    std::shared_ptr<NTween> tween;
    float duration;
    float age = 0;
    bool done = false;

    NTweenParams(std::shared_ptr<NTween> tw, float duration, TweenCallback finishCallback = nullptr) : _finishCallback(finishCallback), tween(tw),
        duration(duration) {}

    bool update(float dt) {
        if (!done) {
            age += dt;
            if (age > duration) {
                age = duration;
                done = true;
            }
            tween->update(age / duration);
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

    std::shared_ptr<NTween> tween(std::shared_ptr<NTween> tw, float duration, TweenCallback cb = nullptr) {
        auto tween = NTweenParams(tw, duration, cb);
        tweens.push_back(tween);
        return tw;
    }
};
