
#pragma once

#include "../deps.h"

class NBasic {
public:
    bool _exists = true;

    virtual void update(float) {} // float dt
    virtual void render(SDL_Surface*) {}
    
    void destroy() {
        this->_exists = false;
    }

    void initialize() {
        this->_exists = true;
    }

    virtual ~NBasic() {}
};
