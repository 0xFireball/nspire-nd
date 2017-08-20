
#include "rng.h"

std::random_device RNG::rd;
std::mt19937 RNG::gen(RNG::rd());
std::uniform_real_distribution<> RNG::dis(0, 1);
