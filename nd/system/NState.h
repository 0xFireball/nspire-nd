
#pragma once

#include "../deps.h"

#include "../util/NColor.h"
#include "../group/NGroup.h"

class NState : public NGroup<NBasic> {
private:
    NColor _clearColor;
public:
    bool created = false;

    NState() : NGroup(0) {}

    virtual void create();
    virtual void update(float); // float dt
    virtual void render(SDL_Surface *surface);

    void setClearColor(NColor col);

    virtual ~NState() {}
};
