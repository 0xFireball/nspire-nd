
#pragma once

#include "../deps.h"
#include "../util/Vec2.h"

#include "../entity/NBasic.h"

class NCamera {
public:
    Vec2 scroll;

    void update(float);

    void render(NG2 &g2, NBasic *drawRoot) {

        // scroll transformation
        g2.pushTransformation(
            Mat33::translation(-scroll.getX(), scroll.getY()));

        drawRoot->render(g2);

        g2.popTransformation(); // scroll
    }
};
