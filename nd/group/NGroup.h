
#pragma once

#include "../deps.h"

#include "../entity/NBasic.h"

template <class T>
class NGroup : public NBasic {
private:
    int _freePosition = 0;

public:
    std::vector<T*> members;
    int memberCount = 0;
    int maxSize = 0;

    NGroup(int maxSize) {
        this->maxSize = maxSize;
    }

    T* add(T* obj) {
        this->members.push_back(obj);
        return obj;
    }

    T* remove(T* obj) {
        this->members.erase(std::remove(this->members.begin(), this->members.end(), obj),
            this->members.end());
        return obj;
    }

    virtual void update(float dt) {
        for (T*& member: this->members) {
            if (member != nullptr && member->_exists) {
                member->update(dt);
            }
        }
        NBasic::update(dt);
    }

    virtual void render(NG2 *g2) {
        for (T*& member: this->members) {
            if (member != nullptr && member->_exists) {
                member->render(g2);
            }
        }
        NBasic::render(g2);
    }

    virtual void destroy() {
        // call destroy on all group members
        for (T*& member: this->members) {
            if (member != nullptr) { member->destroy(); }
        }

        NBasic::destroy();
    }
    
    virtual ~NGroup() {}
};
