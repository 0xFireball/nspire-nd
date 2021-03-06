
#include "NSprite.h"

Rect NSprite::getBounds() const {
    return Rect(this->x + this->offset.getX(), this->y + this->offset.getY(),
                this->width, this->height);
}

void NSprite::loadGraphic(NAssetPath asset, int frameWidth, int frameHeight) {
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
    // create renderBuf
    this->_renderBuf = NG2::create_surface(frameWidth, frameHeight);
}

void NSprite::makeGraphic(int width, int height, NColor col) {
    NG2 renderer;
    this->_graphic = NG2::create_surface(width, height);
    renderer.begin(this->_graphic);
    renderer.clear(col);
    renderer.end();
    this->_horizFrames = 1;
    this->_vertFrames = 1;
    this->_frameWidth = this->width = width;
    this->_frameHeight = this->height = height;
    this->_renderBuf = NG2::create_surface(_frameWidth, _frameHeight);
}

void NSprite::setHitbox(int oX, int oY, int oW, int oH) {
    offset.set(oX, oY);
    width = oW;
    height = oH;
}

void NSprite::update(float dt) { this->animation.update(dt); }

void NSprite::render(NG2 &g2) {
    // render the sprite to the screen
    // MAJOR TODO for improvements
    if (this->_graphic != nullptr) {
        // blit the frame
        int frameX =
            (animation.frameIndex % this->_horizFrames) * this->_frameWidth;
        int frameY =
            (animation.frameIndex / this->_horizFrames) * this->_frameHeight;
        NG2 spriteRenderer;
        spriteRenderer.begin(this->_renderBuf);
        // spriteRenderer.blit_sub_image(this->_graphic,
        //     this->x - this->offset.getX(), this->y - this->offset.getY(),
        //     frameX, frameY,
        //     this->_frameWidth, this->_frameHeight);
        spriteRenderer.blit_sub_image(this->_graphic, Vec2(0, 0), frameX, frameY,
                                      this->_frameWidth, this->_frameHeight);
        spriteRenderer.end();
        SDL_Surface *rot =
            rotozoomSurface(this->_renderBuf, this->angle, 1., 0);
        int xRotOff = rot->w / 2 - this->_renderBuf->w / 2;
        int yRotOff = rot->h / 2 - this->_renderBuf->h / 2;
        // g2.blit_image(rot, this->x - this->offset.getX() - xRotOff,
        //               this->y - this->offset.getY() - yRotOff);
        g2.blit_image(rot, Vec2(this->x - xRotOff, this->y - yRotOff));
        SDL_FreeSurface(rot);
    }
    NEntity::render(g2);
}

void NSprite::destroy() {
    // free _graphic
    if (this->_graphic != nullptr) {
        SDL_FreeSurface(this->_graphic);
        this->_graphic = nullptr;
    }

    // free _renderBuf
    if (this->_renderBuf != nullptr) {
        SDL_FreeSurface(this->_renderBuf);
        this->_renderBuf = nullptr;
    }

    NEntity::destroy();
}
