
#pragma once

#include "../deps.h"

#include "NKeyState.h"

class NKeyInput {
  private:
    std::map<int, NKeyState> _state;

    void fill_position(int k);
    void ensure_position(int k);

  public:
    void pump_keydown(int k, int frame = 0);
    void pump_keyup(int k);

    bool pressed(int key);
    bool anyPressed(const std::vector<int> &keys);

    bool justPressed(int key, int frame);
    bool anyJustPressed(const std::vector<int> &keys, int frame);
};
