//
// Created by scion on 9/5/2022.
//

#include "Entity.h"

Entity::Entity(class Window* window, Entity* parent) : mWindow(window), mParent(parent)  {
}

void Entity::AddComponent(Component *component) {
    mComponents.push_back(component);
}

void Entity::Free() {
    for (Component* mComponent : mComponents) {
        mComponent->Free();
    }
    mComponents.clear();
}

