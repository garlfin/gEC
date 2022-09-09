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
private:
    bool _freed;
protected:
    Entity* const mOwner;
    virtual void OnFree() = 0;
public:
    Component(Entity*, uint64_t);
    virtual ~Component();

    virtual void OnLoad() = 0;
    virtual void OnUpdate(double) = 0;
    virtual void OnRender(double) = 0;

    const Window* Window();
    const Entity* Owner();

    const uint64_t TypeID;

    void Free();
};


#endif //IME_COMPONENT_H
