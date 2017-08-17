
#pragma once

#include "../deps.h"

#define NAssetPath std::string

class NAssetLoader {
  private:
    static std::string _base_path;
  public:
    static void set_base_path(std::string path);
    static std::string get_full_path(std::string subpath);

    static SDL_Surface* load_bmp_ex(std::string path);
};
