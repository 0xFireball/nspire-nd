#pragma once

#include "platform.h"
#include "util/math.h"

// Other
#include <string>
#include <memory>
#include <vector>
#include <deque>
#include <algorithm>
#include <map>
#include <cmath>
#include <random>

#ifdef desktop
#include <iostream>
#endif

#ifndef DISABLE_TWEENS
#include <functional>
#endif

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_config.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>

#if defined(desktop) && defined(ENABLE_TTF)
// SDL_ttf
#include <SDL/SDL_ttf.h>
#endif
