
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

    virtual void render(SDL_Surface *surface) {
        for (T*& member: this->members) {
            if (member != nullptr && member->_exists) {
                member->render(surface);
            }
        }
    }
    
    virtual ~NGroup() {}
};
