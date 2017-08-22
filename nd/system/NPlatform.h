
#pragma once

#include "../deps.h"

class NPlatform {
public:
    #ifdef nspire
    static bool platform_init() {
        return true;
    }
    static bool platform_deinit() {
        return true;
    }
    #elif desktop
    static bool platform_init() {
        // Initialize SDL_ttf
        if (TTF_Init() == -1) {
            return false;
        }
        return true;
    }
    static bool platform_deinit() {
        // quit SDL_ttf
        TTF_Quit();
        return true;
    }
    #endif
};
