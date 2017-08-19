
#pragma once

#include "../deps.h"
#include "../util/NColor.h"
#include "../util/Vec2.h"

/*
    NG2 provides a subset of g2 (Graphics2) API
*/

class NG2 {
  private:
    SDL_Surface *_target;
    std::deque<Mat33> _transforms;

    void apply_transforms(Vec2 &v);

  public:
    void begin(SDL_Surface *target);
    void clear(NColor col);
    void blit_image(SDL_Surface *img, Vec2 pos);
    void blit_sub_image(SDL_Surface *img, Vec2 pos, int sx, int sy, int sw, int sh);
    void end();

    void pushTransformation(Mat33 transform);
    void popTransformation();

    static SDL_Surface *create_surface(int width, int height);
};
