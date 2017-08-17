
#include "NKeyInput.h"

void NKeyInput::pump_keydown(int k) {
    this->ensure_position(k);
    this->_state[k].pump_press();
}

void NKeyInput::pump_keyup(int k) {
    this->ensure_position(k);
    this->_state[k].pump_release();
}

void NKeyInput::ensure_position(int k) {
    if (this->_state.count(k) == 0) { this->fill_position(k); }
}

void NKeyInput::fill_position(int k) {
    this->_state[k] = NKeyState();
}

bool NKeyInput::pressed(int key) {
    this->ensure_position(k);
    NKeyState keyState = this->state[key];
    return keyState.pressed();
}

