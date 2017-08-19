
#pragma once

#include "../system/NGame.h"

class NKeyState {
  private:
    bool _down = false;
    int _pressFrame = 0;

  public:
    void pump_press(int frame = 0) {
        _down = true;
        _pressFrame = frame;
    }

    void pump_release() {
        _down = false;
        _pressFrame = 0;
    }

    bool pressed() {
        return _down;
    }

    bool justPressed(int frame) {
        return pressed() && frame == _pressFrame;
    }
};
