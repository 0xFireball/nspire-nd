
#pragma once

#include "../deps.h"

#include "../entity/NBasic.h"

template <class T> class NGroup : public NBasic {
  private:
    int _freePosition = 0;

  public:
    std::vector<std::shared_ptr<T>> members;
    int memberCount = 0;
    int maxSize = 0;

    NGroup(int maxSize) { this->maxSize = maxSize; }

    std::shared_ptr<T> add(std::shared_ptr<T> obj) {
        this->members.push_back(obj);
        return obj;
    }

    std::shared_ptr<T> remove(std::shared_ptr<T> obj) {
        this->members.erase(
            std::remove(this->members.begin(), this->members.end(), obj),
            this->members.end());
        return obj;
    }

    virtual void update(float dt) {
        for (std::shared_ptr<T> &member : this->members) {
            if (member != nullptr && member->_exists) {
                member->update(dt);
            }
        }
        NBasic::update(dt);
    }

    virtual void render(NG2 *g2) {
        for (std::shared_ptr<T> &member : this->members) {
            if (member != nullptr && member->_exists) {
                member->render(g2);
            }
        }
        NBasic::render(g2);
    }

    virtual void destroy() {
        // call destroy on all group members
        for (std::shared_ptr<T> &member : this->members) {
            if (member != nullptr) {
                member->destroy();
            }
        }

        NBasic::destroy();
    }

    virtual ~NGroup() {}
};
