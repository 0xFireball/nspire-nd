
#pragma once

#include "../system/NGame.h"

#define JUST_PRESSED_FRAMES 1

class NKeyState {
  private:
    bool _down = false;
    int _pressFrame = 0;
    bool _justDown = false;

  public:
    void pump_press(int frame = 0) {
        _down = true;
        _pressFrame = frame;
        _justDown = false;
    }

    void pump_release() {
        _down = false;
        _justDown = false;
    }

    bool pressed() {
        return _down;
    }

    bool justPressed(int frame) {
        _justDown = pressed() && !_justDown && (frame - _pressFrame) <= JUST_PRESSED_FRAMES;
        return _justDown;
    }
};
