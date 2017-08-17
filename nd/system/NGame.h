
#pragma once

#include "../deps.h"
#include "NClock.h"
#include "NState.h"

class NGame {
  private:
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
    static int _frameCount;

    NGame();
    void platform_init(int argc, char **argv);
    void init(int width, int height, int targetFramerate);
    void switch_state(NState *state);
    void start();
    void exit();

#ifdef desktop
// desktop specific
#endif
};
