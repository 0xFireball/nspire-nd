
#pragma once

#include "../ds/NQuadtree.h"
#include "../group/NGroup.h"

class NCollision {

private:
  Rect _bounds;
  NQuadtree _quad;

public:
  NCollision(const Rect &bounds) : _bounds(bounds), _quad(0, bounds) {}

  bool overlap(NEntityRef o1, NEntityRef o2) {
    return Rect::intersect(o1->getBounds(), o2->getBounds());
  }

  bool overlap(
      NEntityRef nt, NEntityGroupRef g2,
      std::function<void(NEntityRef, NEntityRef)> notifyCallback = nullptr) {
    auto g1 = std::make_shared<NEntityGroup>();
    g1->add(nt);
    return overlap(g1, g2, notifyCallback);
  }

  bool overlap(
      NEntityGroupRef g1, NEntityGroupRef g2,
      std::function<void(NEntityRef, NEntityRef)> notifyCallback = nullptr) {

    this->_quad.clear();

    std::vector<NEntityRef> m1 = g1->get_alive();
    std::vector<NEntityRef> m2 = g2->get_alive();

    std::vector<NCollisionEntity> collisionEntities;

    for (int i = 0; i < (int)m1.size(); i++) {
      NCollisionEntity nt = NCollisionEntity(m1[i], m1[i]->getBounds(), 0);
      this->_quad.insert(nt);
      collisionEntities.push_back(nt);
    }

    for (int i = 0; i < (int)m2.size(); i++) {
      NCollisionEntity nt = NCollisionEntity(m2[i], m2[i]->getBounds(), 1);
      this->_quad.insert(nt);
      collisionEntities.push_back(nt);
    }

    std::vector<NCollisionEntity> retColl;

    bool anyCollisions = false;

    for (int i = 0; i < (int)collisionEntities.size(); i++) {
      retColl.clear();

      NCollisionEntity nt = collisionEntities[i];
      this->_quad.retrieve(retColl, nt);

      // narrowphase collision
      for (int j = 0; j < (int)retColl.size(); j++) {
        NCollisionEntity obj = retColl[j];
        // check AABB collision, and ensure they're from different groups
        if (nt.tag != obj.tag && this->overlap(nt.entity, obj.entity)) {
          anyCollisions = true;
          // call notifyCallback
          if (notifyCallback) {
            notifyCallback(nt.entity, obj.entity);
          }
        }
      }
    }

    return anyCollisions;
  }

  bool collide(NEntityRef nt, NEntityGroupRef g2) {
    auto g1 = std::make_shared<NEntityGroup>();
    g1->add(nt);
    return collide(g1, g2);
  }

  bool collide(NEntityGroupRef g1, NEntityGroupRef g2) {
    return this->overlap(g1, g2, NCollision::separate);
  }

  static void separate(NEntityRef e1, NEntityRef e2) {
    // compute overlaps

    float overlapX =
        (e1->width / 2 + e2->width / 2) -
        (std::abs((e1->x + e1->width / 2) - (e2->x + e2->width / 2)));

    float overlapY =
        (e1->height / 2 + e2->height / 2) -
        (std::abs((e1->y + e1->height / 2) - (e2->y + e2->height / 2)));

    if (overlapX < overlapY) {
      float mx;
      if (e1->x > e2->x) {
        mx = -overlapX;
      } else if (e1->x < e2->x) {
        mx = overlapX;
      }
      if (!e1->immovable && !e2->immovable) {
        e1->x -= mx / 2;
        e2->x += mx / 2;
      } else if (e1->immovable) {
        e2->x += mx;
      } else if (e2->immovable) {
        e1->x += mx;
      }
    } else if (overlapY < overlapX) {
      float my;
      if (e1->y > e2->y) {
        my = -overlapY;
      } else if (e1->y < e2->y) {
        my = overlapY;
      }
      if (!e1->immovable && !e2->immovable) {
        e1->y -= my / 2;
        e2->y += my / 2;
      } else if (e1->immovable) {
        e2->y += my;
      } else if (e2->immovable) {
        e1->y += my;
      }
    }
  }
};
