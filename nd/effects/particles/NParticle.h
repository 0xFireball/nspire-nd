
#pragma once

#include "../../util/NColor.h"
#include "../../physics/KinematicSprite.h"

class NParticle : public KinematicSprite {
public:
    float life;
    float age = 0;
    NColor col;

    NParticle(int x, int y, NColor col, float life) : KinematicSprite(x, y), life(life), col(col) {}

    virtual void update(float dt) {
        this->age += dt;

        if (this->age > this->life) {
            // destroy
            this->destroy();
        } else {
            // float alpha = 1 - (age / life);
            // TODO: alpha?
        }
        
        KinematicSprite::update(dt);
    }
};
