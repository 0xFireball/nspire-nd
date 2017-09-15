
/*
    A Quadtree implementation based on
    https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
*/

#pragma once

#include "../deps.h"

#include "../util/Rect.h"

struct NCollisionEntity {
  std::shared_ptr<NEntity> entity;
  Rect bounds;
  int tag;

  NCollisionEntity(std::shared_ptr<NEntity> entity, Rect bounds, int tag = 0)
      : entity(entity), bounds(bounds), tag(tag) {}
};

class NQuadtree {
private:
  static const int MAX_OBJECTS = 10;
  static const int MAX_LEVELS = 5;

  // split the node into 4 subnodes
  void split() {
    int subW = bounds.getW() / 2;
    int subH = bounds.getH() / 2;
    int subX = bounds.getX();
    int subY = bounds.getY();

    nodes[0] = std::make_unique<NQuadtree>(level + 1,
                                           Rect(subX + subW, subY, subW, subH));
    nodes[1] =
        std::make_unique<NQuadtree>(level + 1, Rect(subX, subY, subW, subH));
    nodes[2] = std::make_unique<NQuadtree>(level + 1,
                                           Rect(subX, subY + subH, subW, subH));
    nodes[3] = std::make_unique<NQuadtree>(
        level + 1, Rect(subX + subW, subY + subH, subW, subH));
  }

  /*
  * Determine which node the object belongs to. -1 means
  * object cannot completely fit within a child node and is part
  * of the parent node
  */
  int getIndex(const NCollisionEntity &entity) {
    int index = -1;
    float vertM = bounds.getX() + (bounds.getW() / 2);
    float horizM = bounds.getY() + (bounds.getH() / 2);

    Rect rect = entity.bounds;

    // Object can completely fit within the top quadrants
    bool topQuadrant =
        (rect.getY() < horizM && rect.getY() + rect.getH() < horizM);
    // Object can completely fit within the bottom quadrants
    bool bottomQuadrant = (rect.getY() > horizM);

    // Object can completely fit within the left quadrants
    if (rect.getX() < vertM && rect.getX() + rect.getW() < vertM) {
      if (topQuadrant) {
        index = 1;
      } else if (bottomQuadrant) {
        index = 2;
      }
    }
    // Object can completely fit within the right quadrants
    else if (rect.getX() > vertM) {
      if (topQuadrant) {
        index = 0;
      } else if (bottomQuadrant) {
        index = 3;
      }
    }

    return index;
  }

public:
  int level;
  std::vector<NCollisionEntity> members;
  Rect bounds;
  std::array<std::unique_ptr<NQuadtree>, 4> nodes;

  NQuadtree(int level, const Rect &bounds) : level(level), bounds(bounds) {}

  // clear the quadtree
  void clear() {
    members.clear();

    for (int i = 0; i < (int)nodes.size(); i++) {
      if (nodes[i] != nullptr) {
        nodes[i]->clear();
        nodes[i] = nullptr;
      }
    }
  }

  // Insert an object into the Quadtree. Quadtree will split as needed.
  void insert(const NCollisionEntity &entity) {
    if (nodes[0] != nullptr) {
      int index = this->getIndex(entity);

      if (index > -1) {
        nodes[index]->insert(entity);
        return;
      }
    }

    members.push_back(entity);

    if ((int)members.size() > MAX_OBJECTS && level < MAX_LEVELS) {
      if (nodes[0] == nullptr) {
        this->split();
      }

      int i = 0;
      while (i < (int)members.size()) {
        int index = this->getIndex(members[i]);
        if (index != -1) {
          NCollisionEntity& e = members[i];
          members.erase(members.begin() + i);
          nodes[index]->insert(e);
        } else {
          i++;
        }
      }
    }
  }

  // Return all members that could collide with the given object
  std::vector<NCollisionEntity>
  retrieve(std::vector<NCollisionEntity> &retmembers,
           const NCollisionEntity &entity) {

    int index = this->getIndex(entity);

    if (index > -1 && nodes[0] != nullptr) {
      nodes[index]->retrieve(retmembers, entity);
    }

    retmembers.reserve(retmembers.size() + members.size());
    retmembers.insert(retmembers.end(), members.begin(), members.end());

    return retmembers;
  }
};
