
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
        #ifdef ENABLE_TTF
        // Initialize SDL_ttf
        if (TTF_Init() == -1) {
            return false;
        }
        #endif
        return true;
    }
    static bool platform_deinit() {
        #ifdef ENABLE_TTF
        // quit SDL_ttf
        TTF_Quit();
        #endif
        return true;
    }
    #endif
};
