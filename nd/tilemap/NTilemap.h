
#pragma once

#include "../group/NGroup.h"
#include "NTile.h"

class NTilemap : public NGroup<NTile> {
public:
  int mapWidth;
  int mapHeight;
  std::shared_ptr<NTileset> tileset;
  std::shared_ptr<NTile> *tiles;

  NTilemap(Vec2 offset, int tiles[], int mapWidth, int mapHeight,
           std::shared_ptr<NTileset> tileset)
      : NGroup<NTile>(0), mapWidth(mapWidth), mapHeight(mapHeight),
        tileset(tileset) {
    // create NTile array
    this->tiles = new std::shared_ptr<NTile>[mapWidth * mapHeight];
    for (int r = 0; r < mapHeight; r++) {
      for (int c = 0; c < mapWidth; c++) {
        int tid = r * mapWidth + c;
        int v = tiles[tid];
        if (v > 0) {
          std::shared_ptr<NTile> tile = std::make_shared<NTile>(
              tileset->tileWidth, tileset->tileHeight, v, tileset);
          tile->immovable = true;
          tile->setPosition(
              offset + Vec2(tileset->tileWidth * c, tileset->tileHeight * r));
          this->tiles[tid] = tile;
          this->add(tile);
        }
      }
    }
  }

  virtual void destroy() override {
    delete[] tiles;
    tileset->destroy();
    NGroup<NTile>::destroy();
  }
};
