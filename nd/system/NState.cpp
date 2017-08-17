
#include "NState.h"

void NState::create() {
    this->created = true;
}

void NState::update(float) {
    // Nothing to do, subclass should override
}

void NState::render(SDL_Surface *surface) {
    // clear
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format,
        this->_clearColor.r, this->_clearColor.g, this->_clearColor.b));
    NGroup<NBasic>::render(surface);
}

void NState::setClearColor(NColor col) {
    this->_clearColor = col;
}
