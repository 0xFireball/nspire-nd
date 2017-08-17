
#include "NState.h"

void NState::create() {
    this->created = true;
}

void NState::update(float dt) {
    // Nothing to do, subclass should override
    NGroup<NBasic>::update(dt);
}

void NState::render(NG2 *g2) {
    // clear
    g2->clear(this->_clearColor);
    NGroup<NBasic>::render(g2);
}

void NState::setClearColor(NColor col) {
    this->_clearColor = col;
}
