//
// Created by scion on 9/7/2022.
//

#pragma once

#include <cstdint>
#include "../Managers/ComponentManager.h"

class Entity;
class Window;


class Component {
protected:
    Entity* _Owner;
public:
    Component(Entity*, const std::type_info&);
    virtual ~Component();

    virtual void OnLoad() = 0;
    virtual void OnUpdate(double) = 0;
    virtual void OnRender(double) = 0;
    virtual void OnFree() = 0;

    Window* const Window();
    Entity* const Owner();

    const uint64_t TypeID;

    void Invalidate() { _Owner = nullptr; }
};

