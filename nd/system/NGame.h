
#pragma once

#include "../deps.h"

#include "../input/NKeyInput.h"
#include "NClock.h"
#include "NState.h"
#include "../camera/NCamera.h"

class NKeyInput;

class NGame {
  private:
    int _frameCount;
    SDL_Surface *_screen;
    int _targetFramerate;
    int _targetFramerateTicks;
    std::string _cwd;
    std::unique_ptr<NClock> _clock;
    bool _quit = false;
    NState *_currentState;
    bool _limitFramerate = true;

    void init_vars();

  protected:
    void destroy();
    void game_loop();
    void update(int dt);
    void render();
    void exit();

  public:
    std::unique_ptr<NKeyInput> keys = nullptr;
    int width;
    int height;
    float timeScale = 1.0f;
    NCamera camera;

    NGame();
    void platform_init(int argc, char **argv);
    void init(int width, int height, int targetFramerate);
    void switch_state(NState *state, bool destroy = true);
    void start();
    void quit();
    int get_frame_count();

#ifdef desktop
// desktop specific
#endif
};
