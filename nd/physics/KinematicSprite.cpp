
#include "KinematicSprite.h"

void KinematicSprite::update(float dt) {
    NSprite::update(dt);

    update_motion(dt);
}

void KinematicSprite::update_motion(float dt) {
    float velocityDelta = 0.5f * (compute_velocity(angularVelocity, angularAcceleration, angularDrag, maxAngular, dt) - angularVelocity);
    this->angularVelocity += velocityDelta;
    this->angle += angularVelocity * dt;
    this->angularVelocity += velocityDelta;

    Vec2 pos = this->getPosition();
    float npx = pos.getX();
    float npy = pos.getY();

    float nvx = this->velocity.getX();
    velocityDelta = 0.5f * (compute_velocity(velocity.getX(), acceleration.getX(), drag.getX(), maxVelocity.getX(), dt) - velocity.getX());
    nvx += velocityDelta;
    float delta = nvx * dt;
    nvx += velocityDelta;
    npx += delta;

    float nvy = this->velocity.getY();
    velocityDelta = 0.5f * (compute_velocity(velocity.getY(), acceleration.getY(), drag.getY(), maxVelocity.getY(), dt) - velocity.getY());
    nvy += velocityDelta;
    delta = nvy * dt;
    nvy += velocityDelta;
    npy += delta;

    this->x = npx;
    this->y = npy;

    this->velocity.set(nvx, nvy);
}

float KinematicSprite::compute_velocity(float vel, float acc, float drg, float max, float dt) {
    if (std::abs(acc) > 0) {
        vel += acc * dt;
    }
    else if (std::abs(drg) > 0) {
        float tDrg = drg * dt;
        if (vel - tDrg > 0) {
            vel -= tDrg;
        }
        else if (vel + tDrg < 0) {
            vel += tDrg;
        }
        else {
            vel = 0;
        }
    }
    
    if (std::abs(vel) > 0 && std::abs(max) > 0) {
        if (vel > max) {
            vel = max;
        }
        else if (vel < -max) {
            vel = -max;
        }
    }
    return vel;
}
