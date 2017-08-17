
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

    int getRawTicks() {
        return SDL_GetTicks();
    }

    void update() {
        int now = this->getRawTicks();
        this->_dt = now - this->_last;
        this->_last = now;
    }

    void reset() {
        this->_last = this->getRawTicks();
    }
};
