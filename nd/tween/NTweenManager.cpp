
#ifndef DISABLE_TWEENS
#include "NTweenManager.h"

void NTweenManager::update(float dt) {
    for (NTweenParams &tw : this->tweens) {
        tw.update(dt);
    }

    tweens.erase(
        std::remove_if(tweens.begin(), tweens.end(), [](const NTweenParams &tw) {
            return tw.done;            
        }), tweens.end()
    );

    NBasic::update(dt);
}
#endif
