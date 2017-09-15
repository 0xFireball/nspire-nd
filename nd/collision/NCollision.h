
#pragma once

#include "../ds/NQuadtree.h"

class NCollision {

  typedef std::shared_ptr<NGroup<NEntity>> EntityGroupRef;

private:
  Rect _bounds;
  NQuadtree _quad;

public:
  NCollision(const Rect &bounds) : _bounds(bounds), _quad(0, bounds) {}

  bool overlap(NEntityRef o1, NEntityRef o2) {
    return Rect::intersect(o1->getBounds(), o2->getBounds());
  }

  bool overlap(
      NEntityRef nt, EntityGroupRef g2,
      std::function<void(NEntityRef, NEntityRef)> notifyCallback = nullptr) {
    auto g1 = std::make_shared<NGroup<NEntity>>();
    g1->add(nt);
    return overlap(g1, g2, notifyCallback);
  }

  bool overlap(
      EntityGroupRef g1, EntityGroupRef g2,
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
        if (this->overlap(nt.entity, obj.entity) && nt.tag != obj.tag) {
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

  bool collide(NEntityRef nt, EntityGroupRef g2) {
    auto g1 = std::make_shared<NGroup<NEntity>>();
    g1->add(nt);
    return collide(g1, g2);
  }

  bool collide(EntityGroupRef g1, EntityGroupRef g2) {
    return this->overlap(g1, g2, NCollision::separate);
  }

  static void separate(NEntityRef e1, NEntityRef e2) {
    // compute overlaps

    float overlapX = e1->x + e1->width - e2->x;
    if (e1->x < e2->x) {
      if (overlapX < 0)
        overlapX = 0;
    } else if (e1->x > e2->x) {
      if (overlapX > 0)
        overlapX = 0;
    }
    float overlapY = e1->y + e1->height - e2->y;
    if (e1->y < e2->y) {
      if (overlapY < 0)
        overlapY = 0;
    } else if (e1->y > e2->y) {
      if (overlapY > 0)
        overlapY = 0;
    }

    // separate objects
    if (overlapX > 0) {
      e1->x -= overlapX / 2;
      e2->x += overlapX / 2;
    } else if (overlapX < 0) {
      e1->x += overlapX / 2;
      e2->x -= overlapX / 2;
    }
    if (overlapY > 0) {
      e1->y -= overlapY / 2;
      e2->y += overlapY / 2;
    } else if (overlapY < 0) {
      e1->y += overlapY / 2;
      e2->y -= overlapY / 2;
    }
  }
};
