
#pragma once

#include "../deps.h"

class RNG {
public:
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_real_distribution<> dis;

    static float randf() {
        return (float) RNG::dis(RNG::gen);
    }
};
