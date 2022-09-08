//
// Created by scion on 9/7/2022.
//

#ifndef IME_COMPONENT_H
#define IME_COMPONENT_H


#include <cstdint>

class Entity;
class Window;

class Component {
protected:
    Entity& mOwner;
public:
    Component(Entity&, uint64_t);
    virtual void OnLoad() = 0;
    virtual void OnUpdate(double) = 0;
    virtual void OnRender(double) = 0;
    virtual void OnFree() = 0;

    const Window* Window();
    const Entity* Owner();

    const uint64_t TypeID;
};


#endif //IME_COMPONENT_H
