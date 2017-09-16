
#pragma once

#include "NBasic.h"

#include "../util/Rect.h"
#include "../util/Vec2.h"

class NEntity : public NBasic {
protected:
  void init();

public:
  float x;
  float y;
  float width;
  float height;
  bool immovable;

  NEntity(float x = 0, float y = 0, float width = 0, float height = 0)
      : NBasic(), x(x), y(y), width(width), height(height) {}
  Vec2 getPosition();
  void setPosition(Vec2 pos);
  Vec2 getCenter();
  virtual Rect getBounds() const;
};

typedef std::shared_ptr<NEntity> NEntityRef;
