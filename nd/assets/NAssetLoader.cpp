
#include "NAssets.h"

std::string NAssetLoader::_base_path = "";

void NAssetLoader::set_base_path(std::string path) {
    NAssetLoader::_base_path = path;
}

std::string NAssetLoader::get_full_path(std::string subpath) {
    return NAssetLoader::_base_path + subpath;
}

SDL_Surface* NAssetLoader::load_bmp_ex(std::string path) {
    #if desktop
    return SDL_LoadBMP(path.c_str());
    #elif nspire
    SDL_Surface *rawBmp, *img;
    rawBmp = SDL_LoadBMP(path.c_str());
    if (rawBmp == nullptr) return nullptr;
    // format image for display surface
    img = SDL_DisplayFormat(rawBmp);
    SDL_FreeSurface(rawBmp);
    return img;
    #endif
}
