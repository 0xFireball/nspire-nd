
#pragma once

#include "../assets/NAssets.h"

class NTileset {

public:
  int tileWidth;
  int tileHeight;

  int horizTiles;
  int vertTiles;

  SDL_Surface* _texture;

  NTileset(NAssetPath asset, int tileWidth, int tileHeight)
      : tileWidth(tileWidth), tileHeight(tileHeight) {
    std::string asset_full_path = NAssetLoader::get_full_path(asset);
    SDL_Surface *textureBmp = NAssetLoader::load_bmp_ex(asset_full_path);

    horizTiles = textureBmp->w / tileWidth;
    vertTiles = textureBmp->h / tileHeight;

    _texture = textureBmp;
  }
  void destroy() {
    if (this->_texture) {
      SDL_FreeSurface(this->_texture);
    }
  }
};
