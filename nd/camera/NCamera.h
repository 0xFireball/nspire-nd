
#pragma once

#include "../deps.h"
#include "../util/Vec2.h"

#include "../entity/NBasic.h"
#include "../entity/NEntity.h"

enum NCameraFollowStyle { NONE, LOCKON, DEADZONE };

class NCamera {
private:
  std::shared_ptr<NEntity> _followTarget;

public:
  Vec2 scroll;

  float lerp = 0.2f;

  NCameraFollowStyle followStyle = NCameraFollowStyle::NONE;

  void render(NG2 &g2, std::shared_ptr<NBasic> drawRoot) {

    // scroll transformation
    g2.pushTransformation(Mat33::translation(-scroll.getX(), -scroll.getY()));

    drawRoot->render(g2);

    g2.popTransformation(); // scroll
  }

  void update(float dt) {
    if (followStyle == NCameraFollowStyle::NONE) {
      // ?
    } else if (followStyle == NCameraFollowStyle::LOCKON) {
      // lerp the position
      // scroll.x += (_followTarget->x - scroll.x) * dt * lerp;
      // scroll.y += (_followTarget->y - scroll.y) * dt * lerp;
      scroll += (_followTarget->getCenter() - scroll) * dt * lerp;
    } else if (followStyle == NCameraFollowStyle::DEADZONE) {
      // TODO
    }
  }

  void follow(std::shared_ptr<NEntity> target) { _followTarget = target; }
};
