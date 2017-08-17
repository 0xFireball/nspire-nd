
#pragma once

#include "../system/NGame.h"

#define JUST_PRESSED_FRAMES 1

class NKeyState {
  private:
    bool _down = false;
    int _pressFrame = 0;

  public:
    void pump_press() {
        _down = true;
    }

    void pump_release() {
        _down = false;
    }

    bool pressed() {
        return _down;
    }

    bool justPressed(int frame) {
        return pressed() && (frame - _pressFrame) <= JUST_PRESSED_FRAMES;
    }
};
