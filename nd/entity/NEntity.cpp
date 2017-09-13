
#include "NEntity.h"

void NEntity::init() {
  // TODO
}

Vec2 NEntity::getPosition() { return Vec2(this->x, this->y); }

void NEntity::setPosition(Vec2 pos) {
  this->x = pos.getX();
  this->y = pos.getY();
}

Vec2 NEntity::getCenter() {
  return this->getPosition() + (Vec2(this->width, this->height) / 2);
}

Rect NEntity::getBounds() const {
  return Rect(this->x, this->y, this->width, this->height);
}
