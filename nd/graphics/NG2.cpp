
#include "NG2.h"

void NG2::begin(SDL_Surface *target) { this->_target = target; }

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
