
#pragma once

#include "../assets/NAssets.h"
#include "../entity/NEntity.h"
#include "../graphics/NG2.h"
#include "../util/Vec2.h"
#include "../util/NColor.h"

#include "NAnimationController.h"

class NSprite : public NEntity {
  protected:
    SDL_Surface *_graphic = nullptr;
    SDL_Surface *_renderBuf = nullptr;
    int _vertFrames = 0, _horizFrames = 0;
    int _frameWidth = 0, _frameHeight = 0;

  public:
    NAnimationController animation;
    Vec2 offset;
    float angle = 0;

    NSprite(int x = 0, int y = 0) : NEntity(x, y) {}

    // sprite
    void loadGraphic(NAssetPath asset, int frameWidth = 0,
                     int frameHeight = 0);
    void makeGraphic(int width, int height, NColor col);

    virtual Rect getBounds() const;

    virtual void update(float dt);
    virtual void render(NG2 *g2);

    virtual void destroy();
};
