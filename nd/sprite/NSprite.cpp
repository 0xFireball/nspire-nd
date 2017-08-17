
#include "NSprite.h"

void NSprite::loadGraphic(NAssetPath asset, int frameWidth,
                          int frameHeight, bool animated) {
    // load BMP asset and save to _graphic
    // use asset loader to get full path
    std::string asset_full_path = NAssetLoader::get_full_path(asset);
    SDL_Surface *assetBmp = NAssetLoader::load_bmp_ex(asset_full_path);
    if (animated) {
        // discover frames
        // TODO
    } else {
        if (frameWidth == 0) {
            this->width = assetBmp->w;
        }
        if (frameHeight == 0) {
            this->height = assetBmp->h;
        }
    }
    this->_graphic = assetBmp;
}

void NSprite::render(NG2 *g2) {
    // render the sprite to the screen
    // MAJOR TODO for improvements
    if (this->_graphic != nullptr) {
        // For now, we blit the entire sprite
        // in the future we can blit partial images for animation.
        // TODO: use framewidth and frameheight
        g2->blit_sub_image(this->_graphic, this->x, this->y, 0, 0, this->width, this->height);
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
