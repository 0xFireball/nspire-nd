
#include "NG2.h"

void NG2::begin(SDL_Surface *target) { this->_target = target; }

void NG2::clear(NColor col) {
    SDL_FillRect(this->_target, nullptr,
                 SDL_MapRGB(this->_target->format, col.r, col.g, col.b));
}

void NG2::blit_image(SDL_Surface *img, int x, int y) {
    this->blit_sub_image(img, x, y, 0, 0, img->w, img->h);
}

void NG2::blit_sub_image(SDL_Surface *img, int x, int y, int sx, int sy, int sw,
                         int sh) {
    SDL_Rect subtex;
    subtex.x = sx;
    subtex.y = sy;
    subtex.w = sw;
    subtex.h = sh;

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;

    SDL_BlitSurface(img, &subtex, this->_target, &dstRect);
}

void NG2::end() {}

SDL_Surface *NG2::create_surface(int width, int height) {
    SDL_Surface* sfc = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height,
        DISPLAY_BPP, 0, 0, 0, 0);
    SDL_Surface* surface = SDL_DisplayFormat(sfc);
    SDL_FreeSurface(sfc);
    return surface;
}
