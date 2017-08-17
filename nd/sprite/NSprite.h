
#pragma once

#include "../assets/NAssets.h"
#include "../entity/NEntity.h"

class NSprite : public NEntity {
  protected:
    SDL_Surface *_graphic = nullptr;

  public:
    NSprite(int x = 0, int y = 0) : NEntity(x, y) {}

    // sprite
    void loadGraphic(NAssetPath asset);

    //
    virtual void render(SDL_Surface* screen);
};
