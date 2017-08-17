
#pragma once

#include "../deps.h"
#include "../graphics/NG2.h"

class NBasic {
public:
    bool _exists = true;

    virtual void update(float) {} // float dt
    virtual void render(NG2*) {}
    
    virtual void destroy() {
        this->_exists = false;
    }

    void initialize() {
        this->_exists = true;
    }

    virtual ~NBasic() {}
};
