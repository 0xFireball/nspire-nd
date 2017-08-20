
#pragma once

#include "../deps.h"

#include "../entity/NBasic.h"

template <class T> class NGroup : public NBasic {
  private:
    int _freePosition = 0;

    int getFirstAvailable() {
        int memberContainerSize = (int)members.size();
        for (int i = this->_freePosition; i < memberContainerSize + this->_freePosition; i++) {
            int h = i % memberContainerSize;
            // find null or "nonexistent" member
            if (!members[h] || !members[h]->_exists) {
                _freePosition = h + 1 % memberContainerSize;
                return h;
            }
        }
        return -1;
    }

  public:
    std::vector<std::shared_ptr<T>> members;
    int memberCount = 0;
    int maxSize = 0;

    NGroup(int maxSize) : maxSize(maxSize) {}

    std::shared_ptr<T> add(std::shared_ptr<T> obj) {
        bool full = (int)members.size() >= this->maxSize;
        if (!full) { // members is below capacity, just append
            this->members.push_back(obj);
        } else {
            // attempt to recycle
            int ix = this->getFirstAvailable();
            if (ix < 0) {
                // none available, force kill at _freePosition
                ix = _freePosition;
                --memberCount; // old member is removed
                // force destroy the member
                if (members[ix]->_exists) {
                    members[ix]->destroy();
                }
            }
            // recycle
            members[ix] = obj;
            ++memberCount; // new alive member
        }
        return obj;
    }

    std::shared_ptr<T> remove(std::shared_ptr<T> obj) {
        this->members.erase(
            std::remove(this->members.begin(), this->members.end(), obj),
            this->members.end());
        return obj;
    }

    std::vector<std::shared_ptr<T>> get_alive() {
        // TODO: Filter by alive, valid, etc.
        return members;
    }

    virtual void update(float dt) {
        for (int i = 0; i < (int)this->members.size(); i++) {
            auto member = this->members[i];
            if (member != nullptr && member->_exists) {
                member->update(dt);
                if (!member->_exists) {
                    // member "died"
                    --memberCount;
                    _freePosition = std::min(_freePosition, i);
                }
            }
        }
        NBasic::update(dt);
    }

    virtual void render(NG2 &g2) {
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
            if (member != nullptr && member->_exists) {
                member->destroy();
            }
        }

        NBasic::destroy();
    }

    virtual ~NGroup() {}
};
