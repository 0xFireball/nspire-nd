
#pragma once

#include "NBasic.h"

class NEntity : public NBasic {
  protected:
    void init();

  public:
    int x;
    int y;
    int width;
    int height;

    NEntity(int x = 0, int y = 0, int width = 0, int height = 0)
        : NBasic(), x(x), y(y), width(width), height(height) {}
};
