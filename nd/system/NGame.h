
#pragma once

#include "../deps.h"

#include "../input/NKeyInput.h"
#include "NClock.h"
#include "NState.h"

class NKeyInput;

class NGame {
  private:
    int _frameCount;
    SDL_Surface *_screen;
    int _targetFramerate;
    int _targetFramerateTicks;
    std::string _cwd;
    NClock *_clock;
    bool _quit = false;
    NState *_currentState;

    void init_vars();

  protected:
    void destroy();
    void game_loop();
    void update(int dt);
    void render();

  public:
    NKeyInput *keys = nullptr;

    NGame();
    void platform_init(int argc, char **argv);
    void init(int width, int height, int targetFramerate);
    void switch_state(NState *state);
    void start();
    void exit();
    int get_frame_count();

#ifdef desktop
// desktop specific
#endif
};
