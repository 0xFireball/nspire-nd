
#pragma once

#include "../deps.h"

typedef std::function<float(float)> EaseFunction;

class EaseFunctions {
public:
    static EaseFunction EASE_LINEAR;
    static EaseFunction EASE_SQRT;
};

class NTween {
  public:
    float &_v; // start/current value
    float _s;  // start value
    float _e;  // end value
    EaseFunction _ease;

    NTween(float &v, float e, EaseFunction ease) : _v(v), _ease(ease) {
        float s = v;
        _s = s;
        _e = e;
    }

    // unused except for removing
    NTween& operator= (NTween const&) {
        return *this;
    }

    float update(float t) {
        _v = _s + _ease(t) * (_e - _s);
        return _v;
    }
};

// class NColorTween : public NTween {
// public:
//     float &_v_r;
//     float &_v_g;
//     float &_v_b;

//     NColorTween(NColor) {

//     }
// }
