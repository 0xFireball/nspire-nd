
#pragma once

#include "../deps.h"

class NAnimation {
public:
    int seq[];
    int framerate;

    NAnimation(int seq[], int framerate) : seq(seq), framerate(framerate) {}
};

class NAnimationController {
private:
    float _frameElapsed = 0;
    std::map<std::string, NAnimation*> animations;
    bool _playing = false;
public:
    int frameIndex;
    NAnimation *current;

};
