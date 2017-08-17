
#pragma once

#include "../deps.h"

#include "NKeyState.h"

class NKeyInput {
  private:
    std::map<int, NKeyState> _state;

    void fill_position(int k);

  public:
    void pump_keydown(int k);
    void pump_keyup(int k);
};
