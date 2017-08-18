
#pragma once

#include "../assets/NAssets.h"
#include "../entity/NEntity.h"
#include "../graphics/NG2.h"
#include "NAnimationController.h"

class NSprite : public NEntity {
  protected:
    SDL_Surface *_graphic = nullptr;
    int _vertFrames = 0, _horizFrames = 0;

  public:
    NAnimationController animation;

    NSprite(int x = 0, int y = 0) : NEntity(x, y) {}

    // sprite
    void loadGraphic(NAssetPath asset, int frameWidth = 0,
                     int frameHeight = 0);

    virtual void update(float dt);
    virtual void render(NG2 *g2);

    virtual void destroy();
};
