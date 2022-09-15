//
// Created by scion on 9/5/2022.
//

#ifndef IME_ENTITY_H
#define IME_ENTITY_H

#include <memory>
#include <vector>
#include <iostream>
#include <cstring>
#include "Components/Component.h"

class Window;

class Entity final {
private:
    std::vector<Component*> mComponents;
    Entity* const mParent;
    Window* const mWindow;
public:
    Entity(Window*, Entity* = nullptr);
    ~Entity();

    Window* const Window() { return mWindow; }
    Entity* const Parent() { return mParent; }

    void AddComponent(Component*);

    template<typename T>
    T* GetComponent() {
        uint64_t hashCode = typeid(T).hash_code();
        for (Component* component : mComponents) if (component->TypeID == hashCode) return (T*) component;
        throw std::runtime_error(typeid(T).name());
    };

    void RemoveComponent(Component*);

    void Free();
};


#endif //IME_ENTITY_H
