
#include "NSprite.h"

void NSprite::loadGraphic(NAssetPath asset) {
    // load BMP asset and save to _graphic
    // use asset loader to get full path
    std::string asset_full_path = NAssetLoader::get_full_path(asset);
    SDL_Surface* assetBmp = NAssetLoader::load_bmp_ex(asset_full_path);
    this->_graphic = assetBmp;
}

void NSprite::render(SDL_Surface* screen) {
    // render the sprite to the screen
    // MAJOR TODO for improvements
    if (this->_graphic != nullptr) {
        // For now, we blit the entire sprite
        // in the future we can blit partial images for animation.
        SDL_Rect dstRect;
        dstRect.x = this->x;
        dstRect.y = this->y;
        SDL_BlitSurface(this->_graphic, nullptr, screen, &dstRect);
    }
    NEntity::render(screen);
}
