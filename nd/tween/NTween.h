
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
        if (e < s) {
            float t = e;
            e = s;
            s = t;
        }
        _s = s;
        _e = e;
    }

    NTween& operator= (NTween const& other) {
        _v = other._v;
        _s = other._s;
        _e = other._e;
        _ease = other._ease;
        return *this;
    }

    float update(float t) {
        _v = _s + _ease(t) * (_e - _s);
        return _v;
    }
};
