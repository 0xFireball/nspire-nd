
#pragma once

#include "../deps.h"
#include "../util/NColor.h"

typedef std::function<float(float)> EaseFunction;

class EaseFunctions {
public:
    static EaseFunction EASE_LINEAR;
    static EaseFunction EASE_QUAD_IN;
    static EaseFunction EASE_QUAD_OUT;
};

class NTween {
  public:
    float &_v; // start/current value
    float _s;  // start value
    float _e;  // end value
    EaseFunction _ease;
    bool done = false;

    NTween(float &v, float e, EaseFunction ease) : _v(v), _ease(ease) {
        float s = v;
        _s = s;
        _e = e;
    }

    // unused except for removing
    NTween& operator= (NTween const&) {
        return *this;
    }

    virtual float update(float t) {
        _v = _s + _ease(t) * (_e - _s);
        done = t >= 1.0;
        return _v;
    }
};

class NColorTween : public NTween {
private:
    NTween _rT;
    NTween _gT;
    NTween _bT;

    float _v = 0;

public:

    NColorTween(NColor &startCol, NColor endCol, EaseFunction ease) : NTween(_v, 0, ease),
        _rT(startCol.r, endCol.r, ease), _gT(startCol.g, endCol.g, ease), _bT(startCol.b, endCol.b, ease) {
    }

    virtual float update(float t) {
        _rT.update(t);
        _gT.update(t);
        _bT.update(t);

        return NTween::update(t);
    }
};
