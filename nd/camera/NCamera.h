
#pragma once

#include "../deps.h"
#include "../util/Vec2.h"

#include "../entity/NBasic.h"

class NCamera {
public:
    void update(float);

    void render(NG2 &g2, NBasic *drawRoot) {
        // TODO: Transformations
        drawRoot->render(g2);
    }
};
