
#pragma once

#include "rng.h"

#define COL_FLOAT_CONV 255.999

struct NColor {
    float r, g, b;
    NColor() : r(0), g(0), b(0) {}    
    NColor(float r, float g, float b) : r(r), g(g), b(b) {}
    NColor(float v) : NColor(v, v, v) {}
    
    static NColor fromRGBInt(int r, int g, int b) {
        return NColor(r / COL_FLOAT_CONV,
            g / COL_FLOAT_CONV,
            b / COL_FLOAT_CONV);
    }

    int fmt(float v) { return v * COL_FLOAT_CONV; }

    static NColor rand_col(float r, float g, float b, float variation = 0.1) {
        float colDiff = RNG::randf() * (variation * 2) - variation;
        return NColor(r + colDiff, g + colDiff, b + colDiff);
    }
};
