
#pragma once

#include "../deps.h"
#include "../util/NColor.h"

/*
    NG2 provides a subset of g2 (Graphics2) API
*/

class NG2 {
  private:
    SDL_Surface *_target;

  public:
    void begin(SDL_Surface *target);
    void clear(NColor col);
    void blit_image(SDL_Surface *img, int x, int y);
    void blit_sub_image(SDL_Surface *img, int x, int y, int sx, int sy, int sw,
                        int sh);
    void end();

    static SDL_Surface *create_surface(int width, int height);
};
