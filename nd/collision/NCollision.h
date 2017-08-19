
#pragma once

#include "../ds/NQuadtree.h"

class NCollision {
  private:
    Rect _bounds;

  public:
    NCollision(const Rect &bounds) : _bounds(bounds) {}

    bool overlap(const NEntity &o1, const NEntity &o2) {
        return Rect::intersect(o1.getBounds(), o2.getBounds());
    }

    // bool overlap(const NGroup<NEntity> &g1, const NGroup<NEntity> &g2) {
    //     // TODO
    //     return false;
    // }
};