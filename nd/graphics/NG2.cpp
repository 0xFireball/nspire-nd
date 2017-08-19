
#include "NG2.h"

void NG2::begin(SDL_Surface *target) { this->_target = target; }

void NG2::clear(NColor col) {
    SDL_FillRect(this->_target, nullptr,
                 SDL_MapRGB(this->_target->format, col.fmt(col.r), col.fmt(col.g), col.fmt(col.b)));
}

void NG2::blit_image(SDL_Surface *img, Vec2 pos) {
    this->blit_sub_image(img, pos, 0, 0, img->w, img->h);
}

void NG2::blit_sub_image(SDL_Surface *img, Vec2 pos, int sx, int sy, int sw,
                         int sh) {
    SDL_Rect subtex;
    subtex.x = sx;
    subtex.y = sy;
    subtex.w = sw;
    subtex.h = sh;

    this->apply_transforms(pos);

    SDL_Rect dstRect;
    dstRect.x = pos.getX();
    dstRect.y = pos.getY();

    SDL_BlitSurface(img, &subtex, this->_target, &dstRect);
}

void NG2::end() {}

void NG2::apply_transforms(Vec2 &v) {
    for (int i = 0; i < (int)this->_transforms.size(); i++) {
        v.transform(this->_transforms[i]);
    }
}

void NG2::pushTransformation(Mat33 transform) {
    this->_transforms.push_front(transform);
}

void NG2::popTransformation() {
    this->_transforms.pop_front();
}

SDL_Surface *NG2::create_surface(int width, int height) {
    SDL_Surface* sfc = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height,
        DISPLAY_BPP, 0, 0, 0, 0);
    SDL_Surface* surface = SDL_DisplayFormat(sfc);
    SDL_FreeSurface(sfc);
    return surface;
}
