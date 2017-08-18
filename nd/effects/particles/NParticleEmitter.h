
#pragma once

#include "../../group/NGroup.h"
#include "../../util/Vec2.h"
#include "NParticle.h"

class NParticleEmitter : public NGroup<NParticle> {
public:
    NParticleEmitter(int maxSize) : NGroup<NParticle>(maxSize) {}

    void emitSquare(int x, int y, int size, Vec2 velocity, NColor col, float life) {
        x -= size / 2;
        y -= size / 2;
        NParticle *particle = new NParticle(x, y, col, life);
        particle->makeGraphic(x, y, col);
        particle->velocity = velocity;
        this->add(particle);
    }
};
