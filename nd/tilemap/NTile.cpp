
#include "NTile.h"

void NTile::render(NG2 &g2) {
  int tsX =
      (this->index % this->tileset->horizTiles) * this->tileset->tileWidth;
  int tsY =
      (this->index / this->tileset->horizTiles) * this->tileset->tileHeight;

  g2.blit_sub_image(this->tileset->_texture, Vec2(this->x, this->y), tsX, tsY,
                    this->tileset->tileWidth, this->tileset->tileHeight);

  NEntity::render(g2);
}
