
#pragma once

#include "../deps.h"
#include "NState.h"
#include "NClock.h"

class NGame {
  private:
    SDL_Surface *_screen;
    int _targetFramerate;
    int _targetFramerateTicks;
    std::string _cwd;
    int _frameCount;
    NClock* _clock;
    bool _quit = false;
    NState* _currentState;

    void init_vars();

  protected:
    void destroy();
    void game_loop();
    void update(int dt);
    void render();

  public:
    NGame();
    void platform_init(int argc, char** argv);
    void init(int width, int height, int targetFramerate);
    void switch_state(NState* state);
    void start();
    void exit();

#ifdef desktop
// desktop specific
#endif
};
