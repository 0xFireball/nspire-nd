
#pragma once

#include "../deps.h"
#include "../util/array.h"

class NAnimation {
  public:
    std::vector<int> seq;
    int framerate;

    NAnimation(std::vector<int> seq, int framerate)
        : seq(seq), framerate(framerate) {}
};

class NAnimationController {
  private:
    float _frameElapsed = 0;
    std::map<std::string, std::shared_ptr<NAnimation>> _animations;
    bool _playing = false;

  public:
    int frameIndex = 0;
    std::shared_ptr<NAnimation> current;

    void add(std::string name, std::vector<int> sequence, int framerate) {
        this->_animations[name] =
            std::make_shared<NAnimation>(sequence, framerate);
    }

    void play(std::string name, bool force = false) {
        if (!this->_playing || force) {
            this->current = this->_animations[name];
            this->frameIndex = 0;
            this->_playing = true;
        }
    }

    void stop() {
        this->_playing = false;
        this->current.reset();
        this->_frameElapsed = 0;
    }

    void update(float dt) {
        if (this->_playing) {
            float frameTime = 1.0f / this->current->framerate;
            if (this->_frameElapsed < frameTime) {
                this->_frameElapsed += dt;
            } else {
                // switch frames
                if (this->frameIndex >= ((int)this->current->seq.size()) - 1) {
                    // last frame, end animation
                    this->stop();
                } else {
                    this->frameIndex++;
                }
                this->_frameElapsed = 0;
            }
        }
    }
};
