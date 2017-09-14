
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

  Vec2 bounds;

  void reset() {
    lerp = 0.2f;
    followStyle = NCameraFollowStyle::NONE;
    _followTarget.reset();
    scroll.set(0, 0);
  }

  void render(NG2 &g2, std::shared_ptr<NBasic> drawRoot) {

    // scroll transformation
    g2.pushTransformation(Mat33::translation(-scroll.getX(), -scroll.getY()));

    drawRoot->render(g2);

    g2.popTransformation(); // scroll
  }

  void update(float) {
    if (followStyle == NCameraFollowStyle::NONE) {
      // ?
    } else if (followStyle == NCameraFollowStyle::LOCKON) {
      // lerp the position
      Vec2 targetScroll = _followTarget->getCenter() - (bounds / 2);
      scroll += (targetScroll - scroll) * lerp;
      // std::cout << scroll.getX() << " " << scroll.getY() << std::endl;
    } else if (followStyle == NCameraFollowStyle::DEADZONE) {
      // TODO
    }
  }

  void follow(std::shared_ptr<NEntity> target) { _followTarget = target; }
};
