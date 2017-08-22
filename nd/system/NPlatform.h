
#pragma once

#include "../deps.h"

class NPlatform {
public:
    #ifdef nspire
    static void platform_init() {
    }
    static void platform_deinit() {
    }
    #elif desktop
    static void platform_init() {
    }
    static void platform_deinit() {
    }
    #endif
};
