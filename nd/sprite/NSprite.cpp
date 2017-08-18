
#include "NSprite.h"

void NSprite::loadGraphic(NAssetPath asset, int frameWidth,
                          int frameHeight) {
    // load BMP asset and save to _graphic
    // use asset loader to get full path
    std::string asset_full_path = NAssetLoader::get_full_path(asset);
    SDL_Surface *assetBmp = NAssetLoader::load_bmp_ex(asset_full_path);

    if (frameWidth == 0) {
        frameWidth = this->width = assetBmp->w;
    } else {
        this->width = frameWidth;
    }
    if (frameHeight == 0) {
        frameHeight = this->height = assetBmp->h;
    } else {
        this->height = frameHeight;
    }

    this->_vertFrames = assetBmp->h / frameHeight;
    this->_horizFrames = assetBmp->w / frameWidth;

    this->_frameWidth = this->width;
    this->_frameHeight = this->height;

    this->_graphic = assetBmp;
}

void NSprite::update(float dt) {
    this->animation.update(dt);
}

void NSprite::render(NG2 *g2) {
    // render the sprite to the screen
    // MAJOR TODO for improvements
    if (this->_graphic != nullptr) {
        // blit the frame
        int frameX = (animation.frameIndex % this->_horizFrames) * this->_frameWidth;
        int frameY = (animation.frameIndex / this->_horizFrames) * this->_frameHeight;
        g2->blit_sub_image(this->_graphic,
            this->x - this->offset.getX(), this->y - this->offset.getY(),
            frameX, frameY,
            this->_frameWidth, this->_frameHeight);
    }
    NEntity::render(g2);
}

void NSprite::destroy() {
    // free _graphic
    if (this->_graphic != nullptr) {
        SDL_FreeSurface(this->_graphic);
        this->_graphic = nullptr;
    }

    NEntity::destroy();
}
