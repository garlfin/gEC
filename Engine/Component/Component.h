//
// Created by scion on 9/7/2022.
//

#ifndef IME_COMPONENT_H
#define IME_COMPONENT_H


#include <cstdint>
#include "ComponentManager.h"

class Entity;
class Window;


class Component {
protected:
    Entity* mOwner;
public:
    Component(Entity*, uint64_t);
    virtual ~Component();

    virtual void OnLoad() = 0;
    virtual void OnUpdate(double) = 0;
    virtual void OnRender(double) = 0;
    virtual void OnFree() = 0;

    Window* const Window();
    Entity* const Owner();

    const uint64_t TypeID;

    void Invalidate() { mOwner = nullptr; }
};


#endif //IME_COMPONENT_H
