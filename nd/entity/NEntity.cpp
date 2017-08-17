
#include "NEntity.h"

void NEntity::init() {
    // TODO
}

Vec2 NEntity::getPosition() {
    return Vec2(this->x, this->y);
}

void NEntity::setPosition(Vec2 pos) {
    this->x = pos.getX();
}
