
#include "NKeyInput.h"

void NKeyInput::pump_keydown(int k) {
    if (this->_state.count(k) == 0) { this->fill_position(k); }
    this->_state[k].pump_press();
}

void NKeyInput::pump_keyup(int k) {
    if (this->_state.count(k) == 0) { this->fill_position(k); }
    this->_state[k].pump_release();
}

void NKeyInput::fill_position(int k) {
    this->_state[k] = NKeyState();
}
