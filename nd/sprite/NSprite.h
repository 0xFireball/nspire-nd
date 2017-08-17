
#pragma once

#include "../assets/NAssets.h"
#include "../entity/NEntity.h"

class NSprite : public NEntity {
  protected:
    SDL_Surface *_graphic = nullptr;

  public:
    NSprite(int x = 0, int y = 0) : NEntity(x, y) {}

    // sprite
    void loadGraphic(NAssetPath asset, int frameWidth = 0,
                     int frameHeight = 0, bool animated = false);

    //
    virtual void render(SDL_Surface *screen);

    virtual void destroy();
};
