
#pragma once

#include "../deps.h"

#include "../graphics/NG2.h"
#include "../group/NGroup.h"
#include "../util/NColor.h"

class NGame;

class NState : public NGroup<NBasic> {
  private:
    NColor _clearColor;

  public:
    bool created = false;
    NGame *game;

    NState() : NGroup(0) {}

    virtual void create();
    virtual void update(float dt);
    virtual void render(NG2 &g2);

    void setClearColor(NColor col);

    virtual ~NState() {
      this->game = nullptr;
    }
};
