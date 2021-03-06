
#include "NGame.h"
#include "../assets/NAssets.h"
#include "NPlatform.h"

NGame::NGame() {}

void NGame::platform_init(int argc, char **argv) {
  if (argc > 0) {
    char *program = argv[0];
    std::string cwd = program;
    cwd = cwd.substr(0, cwd.find_last_of('/') + 1);
    this->_cwd = cwd;
    // set asset path
    NAssetLoader::set_base_path(cwd);
  }
  NPlatform::platform_init();
}

void NGame::platform_deinit() { NPlatform::platform_deinit(); }

void NGame::init(int width, int height, int targetFramerate) {
  SDL_Init(SDL_INIT_VIDEO);
  if (width == 0)
    width = DISPLAY_WIDTH;
  if (height == 0)
    height = DISPLAY_HEIGHT;
  this->_screen = SDL_SetVideoMode(width, height, DISPLAY_BPP, SDL_SWSURFACE);
  this->width = width;
  this->height = height;

  this->_targetFramerate = targetFramerate;
  this->_targetFramerateTicks = 1000 / targetFramerate;

  // initialize
  this->init_vars();

  // prepare rendering loop
  this->_clock = std::make_unique<NClock>();

  // initialize keyboard system
  this->keys = std::make_unique<NKeyInput>();

  // initialize camera
  camera.bounds.set(this->width, this->height);
}

void NGame::switch_state(std::shared_ptr<NState> state, bool destroy) {
  if (this->_currentState && destroy) {
    this->_currentState->destroy();
    this->_currentState = nullptr;
  }
  if (state != nullptr) {
    state->game = this;
    if (!state->created) {
      state->create();
    }
  }
  this->_currentState = state;
}

void NGame::init_vars() { this->_frameCount = 0; }

void NGame::destroy() {
  // delete the current state
  this->switch_state(nullptr);

  // free SDL surface
  SDL_FreeSurface(this->_screen);

  // free other resources
}

void NGame::exit() {
  this->destroy();
  SDL_Quit();
}

void NGame::quit() { this->_quit = true; }

void NGame::start() {
  this->_clock->reset();
  this->game_loop();
}

void NGame::game_loop() {
  while (!this->_quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        this->quit();
        break;
      case SDL_KEYDOWN:
        this->keys->pump_keydown(event.key.keysym.sym, this->_frameCount);
        break;
      case SDL_KEYUP:
        this->keys->pump_keyup(event.key.keysym.sym);
        break;
      }
    }

    // loop frame
    this->_clock->update();
    int dt = this->_clock->getElapsed();
    int renderStart = this->_clock->getRawTicks();

    this->update(dt);
    this->render();

    int renderTime = this->_clock->getRawTicks() - renderStart;

    this->_frameCount++;

    // framerate cap
    if (this->_limitFramerate) {
      // limit framerate based on render time
      int aheadTime = this->_targetFramerateTicks - renderTime;
      if (aheadTime > 0) {
        SDL_Delay(aheadTime); // sleep
      } else {
#if GRAPHICS_DEBUG
        std::cout << "dropped frame " << this->_frameCount + 1 << std::endl;
#endif
      }
    }
  }
  // exit
  this->exit();
}

void NGame::update(int mdt) {
  // update the current state
  float dt = (mdt / 1000.0f);
  this->camera.update(dt);
  this->_currentState->update(dt * this->timeScale);
}

void NGame::render() {
  // create a g2
  NG2 g2;
  g2.begin(this->_screen);
  // render the current state
  this->camera.render(g2, this->_currentState);
  g2.end();
  // flip the buffers
  SDL_Flip(this->_screen);
}

int NGame::get_frame_count() { return this->_frameCount; }

#ifdef desktop
// Desktop-specific
#endif
