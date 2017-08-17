
#pragma once

#include "../deps.h"

class NClock {
private:
    int _last = 0;
    int _dt = 0;
public:
    NClock() {
    }

    int getElapsed() {
        return _dt;
    }

    void update() {
        int now = SDL_GetTicks();
        this->_dt = now - this->_last;
        this->_last = now;
    }

    void reset() {
        this->_last = SDL_GetTicks();
    }
};
