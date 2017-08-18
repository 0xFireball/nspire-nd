
#pragma once

#include "../deps.h"

#include "../sprite/NSprite.h"

class KinematicSprite : public NSprite {
private:
    float compute_velocity(float vel, float acc, float drg, float max, float dt);

protected:
    void update_motion(float dt);

public:
    KinematicSprite(int x, int y) : NSprite(x, y) {}

    Vec2 velocity;
    Vec2 maxVelocity;
    Vec2 acceleration;
    Vec2 drag;

    float angularVelocity = 0;
    float maxAngular = 0;
    float angularAcceleration = 0;
    float angularDrag = 0;

    virtual void update(float dt);
};
