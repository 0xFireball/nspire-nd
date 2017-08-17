
#include "NGame.h"
#include "../assets/NAssets.h"

NGame::NGame() {}

void NGame::platform_init(int argc, char** argv) {
    if (argc > 0) {
        char* program = argv[0];
        std::string cwd = program;
        cwd = cwd.substr(0, cwd.find_last_of('/') + 1);
        this->_cwd = cwd;
        // set asset path
        NAssetLoader::set_base_path(cwd);
    }
}

void NGame::init(int width, int height, int targetFramerate) {
    SDL_Init(SDL_INIT_VIDEO);
    if (width == 0) width = DISPLAY_WIDTH;
    if (height == 0) height = DISPLAY_HEIGHT;
    this->_screen = SDL_SetVideoMode(width, height, DISPLAY_BPP, SDL_SWSURFACE);

    this->_targetFramerate = targetFramerate;
    this->_targetFramerateTicks = 1000 / targetFramerate;

    // initialize
    this->init_vars();

    // prepare rendering loop
    this->_clock = new NClock();
}

void NGame::switch_state(NState* state) {
    if (this->_currentState != nullptr) delete this->_currentState;
    if (!state->created) state->create();
    this->_currentState = state;
}

void NGame::init_vars() {
    this->_frameCount = 0;
}

void NGame::destroy() {
    // delete the current state
    this->switch_state(nullptr);

    // free SDL surface
    SDL_FreeSurface(this->_screen);

    // free other resources
    if (this->_clock != nullptr) delete this->_clock;
}

void NGame::exit() {
    this->destroy();
    SDL_Quit();
}

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
                    this->_quit = true;
            }
        }

        // loop frame
        this->_clock->update();
        int dt = this->_clock->getElapsed();

        this->update(dt);
        this->render();

        this->_frameCount++;

        // limit framerate
        int aheadTime = this->_targetFramerateTicks - dt;
        if (aheadTime > 0) {
            SDL_Delay(aheadTime); // sleep
        }
    }
}

void NGame::update(int dt) {
    // update the current state
    this->_currentState->update(dt / 1000.0f);
}

void NGame::render() {
    // render the current state
    this->_currentState->render(this->_screen);
    // flip the buffers
    SDL_Flip(this->_screen);
}

#ifdef desktop
// Desktop-specific
#endif
