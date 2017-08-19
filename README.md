
# nspire-nd

a simple cross-platform (desktop+ndless) 2d graphics lib


## What, exactly?

`ndless` for the TI Nspire includes an implementation of SDL1.2.
This library provides an abstracted 2d rendering API allowing
you to write code that will run unmodified both natively
on your x86 desktop and on your TI Nspire. For example, I can
run the `bouncyball` program on both my Linux computer and
on my TI Nspire simply by changing the build target.

Features include a framerate-limited game loop and
cross-platform BMP loading and SDL rendering.

## Build/run this demo

Build for ndless:
`make DISTDIR=binspire XPLAT_TARGET=nspire`

Build for linux (or any desktop, really):
`make DISTDIR=linux XPLAT_TARGET=desktop`

## What the API looks like

`main.cpp`
```cpp
#include <memory>

#include "deps.h"

#include "states/gamestate.h"

int main(int argc, char **argv) {
    auto game = std::make_shared<NGame>();

    game->platform_init(argc, argv);

    // Initialize NGame at max screen size, 30FPS target
    game->init(0, 0, 30);
    game->switch_state(std::make_shared<GameState>);
    game->start();

    return 0;
}
```

`gamestate.cpp`
```cpp
#include "gamestate.h"

void GameState::create() {

    this->setClearColor(NColor(0.0f));

    auto ball = std::make_shared<Ball>(20, 20);
    ball->loadGraphic("ball.bmp.tns");
    this->add(ball);

    // TODO: Add more sprites and objects

    NState::create();
}

void GameState::update(float dt) {

    // TODO: Add additional custom update logic

    bool esc = this->game->keys->pressed(SDLK_ESCAPE);
    if (esc) {
        this->game->quit();
    }

    NState::update(dt);
}
```

