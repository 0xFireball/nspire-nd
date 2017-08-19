
#ifdef ENABLE_TWEENS
#include "NTween.h"

EaseFunction EaseFunctions::EASE_LINEAR = [](float t) { return t; };
EaseFunction EaseFunctions::EASE_QUAD_IN = [](float t) { return t * t; };
EaseFunction EaseFunctions::EASE_QUAD_OUT = [](float t) { return -t * (t - 2); };
#endif
