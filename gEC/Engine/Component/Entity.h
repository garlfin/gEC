//
// Created by scion on 9/5/2022.
//

#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <cstring>
#include "Components/Component.h"

class Window;

class Entity final {
private:
    std::vector<Component*> components;
    Entity* const parent;
    Window* const window;
public:
    Entity(Window*, Entity* = nullptr);
    ~Entity();

    Window* const Window() { return window; }
    Entity* const Parent() { return parent; }

    void AddComponent(Component*);

    template<typename T>
    T* GetComponent() {
        uint64_t hashCode = typeid(T).hash_code();
        for (Component* component : components) if (component->TypeID == hashCode) return (T*) component;
        throw std::runtime_error(typeid(T).name());
    };

    void RemoveComponent(Component*);

    void Free();
};


