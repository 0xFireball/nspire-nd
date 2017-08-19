
#pragma once

#include "../ds/NQuadtree.h"

class NCollision {
  private:
    Rect _bounds;
    NQuadtree _quad;

  public:
    NCollision(const Rect &bounds) : _bounds(bounds), _quad(0, bounds) {}

    bool overlap(const NEntity &o1, const NEntity &o2) {
        return Rect::intersect(o1.getBounds(), o2.getBounds());
    }

    // bool overlap(const NGroup<NEntity> &g1, const NGroup<NEntity> &g2) {
    //     this->_quad.clear();

    //     std::vector<std::shared_ptr<NEntity>> m1 = g1.get_alive();
    //     std::vector<std::shared_ptr<NEntity>> m2 = g2.get_alive();

    //     for (int i = 0; i < (int)m1.size(); i++) {
    //         this->_quad.insert(m1[i]->getBounds());
    //     }

    //     for (int i = 0; i < (int)m2.size(); i++) {
    //         this->_quad.insert(m2[i]->getBounds());
    //     }

    //     return false;
    // }
};
