

#pragma once

#include "../entity/NEntity.h"
#include "NTileset.h"

class NTile : public NEntity {
public:
  int index;
  std::shared_ptr<NTileset> tileset;

  NTile(int width, int height, int index, std::shared_ptr<NTileset> tileset)
      : NEntity(0, 0, width, height), index(index), tileset(tileset) {}

  virtual void render(NG2 &g2);
};
