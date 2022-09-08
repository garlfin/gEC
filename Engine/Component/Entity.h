//
// Created by scion on 9/5/2022.
//

#ifndef IME_ENTITY_H
#define IME_ENTITY_H

#include <memory>
#include <vector>
#include "Component.h"

class Window;

class Entity final {
private:
    std::vector<Component*> mComponents;
    const Entity* mParent;
    const Window* mWindow;
public:
    Entity(Window*, Entity* = nullptr);
    const Window* Window() { return mWindow; }
    const Entity* Parent() { return mParent; }

    void AddComponent(Component*);

    template<typename T>
    T* GetComponent() {
        uint64_t hashCode = typeid(T).hash_code();
        for (Component* component : mComponents) if (component->TypeID == hashCode) return (T*) component;
        return nullptr;
    };

    void Free();
};


#endif //IME_ENTITY_H
