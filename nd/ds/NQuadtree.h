
/*
    A Quadtree implementation based on
    https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
*/

#pragma once

#include "../deps.h"

#include "../util/Rect.h"

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

        nodes[0] = std::make_unique<NQuadtree>(
            level + 1, Rect(subX + subW, subY, subW, subH));
        nodes[1] = std::make_unique<NQuadtree>(level + 1,
                                               Rect(subX, subY, subW, subH));
        nodes[2] = std::make_unique<NQuadtree>(
            level + 1, Rect(subX, subY + subH, subW, subH));
        nodes[3] = std::make_unique<NQuadtree>(
            level + 1, Rect(subX + subW, subY + subH, subW, subH));
    }

    /*
    * Determine which node the object belongs to. -1 means
    * object cannot completely fit within a child node and is part
    * of the parent node
    */
    int getIndex(const Rect &rect) {
        int index = -1;
        float vertM = bounds.getX() + (bounds.getW() / 2);
        float horizM = bounds.getY() + (bounds.getH() / 2);

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
    std::vector<Rect> objects;
    Rect bounds;
    std::array<std::unique_ptr<NQuadtree>, 4> nodes;

    NQuadtree(int level, const Rect &bounds) : level(level), bounds(bounds) {}

    // clear the quadtree
    void clear() {
        objects.clear();

        for (int i = 0; i < (int)nodes.size(); i++) {
            if (nodes[i] != nullptr) {
                nodes[i]->clear();
                nodes[i] = nullptr;
            }
        }
    }

    // Insert an object into the Quadtree. Quadtree will split as needed.
    void insert(const Rect &rect) {
        if (nodes[0] != nullptr) {
            int index = this->getIndex(rect);

            if (index > -1) {
                nodes[index]->insert(rect);
                return;
            }
        }

        objects.push_back(rect);

        if ((int)objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
            if (nodes[0] == nullptr) {
                this->split();
            }

            int i = 0;
            while (i < (int)objects.size()) {
                int index = this->getIndex(objects[i]);
                if (index != -1) {
                    // objects.remove(i)
                    Rect o = objects[i];
                    objects.erase(
                        std::remove(objects.begin(), objects.end(), o),
                        objects.end());
                    nodes[index]->insert(o);
                } else {
                    i++;
                }
            }
        }
    }

    // Return all objects that could collide with the given object
    std::vector<Rect> retrieve(std::vector<Rect> &retObjects,
                               const Rect &rect) {
        int index = this->getIndex(rect);

        if (index > -1 && nodes[0] != nullptr) {
            nodes[index]->retrieve(retObjects, rect);
        }

        retObjects.reserve(retObjects.size() + objects.size());
        retObjects.insert(retObjects.end(), objects.begin(), objects.end());

        return retObjects;
    }
};
