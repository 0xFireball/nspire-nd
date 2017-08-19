
#ifdef ENABLE_TWEENS
#include "NTween.h"

EaseFunction EaseFunctions::EASE_LINEAR = [](float t) { return t; };
EaseFunction EaseFunctions::EASE_SQRT = [](float t) { return std::sqrt(t); };
#endif
