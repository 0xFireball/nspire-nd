
#include "NKeyInput.h"

void NKeyInput::pump_keydown(int k, int frame) {
    this->ensure_position(k);
    this->_state[k].pump_press(frame);
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

bool NKeyInput::anyPressed(const std::vector<int> &keys) {
    for (int i = 0; i < (int)keys.size(); i++) {
        if (this->pressed(keys[i])) return true;
    }
    return false;
}

bool NKeyInput::justPressed(int key, int frame) {
    this->ensure_position(key);
    NKeyState keyState = this->_state[key];
    return keyState.justPressed(frame);
}

bool NKeyInput::anyJustPressed(const std::vector<int> &keys, int frame) {
    for (int i = 0; i < (int)keys.size(); i++) {
        if (this->justPressed(keys[i], frame)) return true;
    }
    return false;
}
