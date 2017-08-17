
#include "NKeyInput.h"
#include "../util/array.h"

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
    this->ensure_position(key);
    NKeyState keyState = this->_state[key];
    return keyState.pressed();
}

bool NKeyInput::anyPressed(int keys[]) {
    for (int i = 0; i < arr_size<int>(keys); i++) {
        if (this->pressed(keys[i])) return true;
    }
    return false;
}
