
#pragma once

#include "../../group/NGroup.h"
#include "../../util/Vec2.h"
#include "../../util/math.h"
#include "../../util/rng.h"
#include "NParticle.h"

class NParticleEmitter : public NEntityGroup {
public:
    NParticleEmitter(int maxSize) : NEntityGroup(maxSize) {}

    void emitSquare(int x, int y, int size, Vec2 velocity, NColor col, float life) {
        x -= size / 2;
        y -= size / 2;
        std::shared_ptr<NParticle> particle = std::make_shared<NParticle>(x, y, col, life);
        particle->makeGraphic(size, size, col);
        particle->velocity = velocity;
        this->add(particle);
    }

    static Vec2 velocity_spread(float radius, float xOffset = 0, float yOffset = 0) {
        float theta = RNG::randf() * PI * 2;
		float u = RNG::randf() + RNG::randf();
		float r = radius * (u > 1 ? 2 - u : u);
        return Vec2(std::cos(theta) * r + xOffset, std::sin(theta) * r + yOffset);
    }
};
