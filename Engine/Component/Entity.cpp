//
// Created by scion on 9/5/2022.
//

#include "Entity.h"

Entity::Entity(class Window* window, Entity* parent) : mWindow(window), mParent(parent)  {
}

void Entity::AddComponent(Component *component) {
    mComponents.push_back(component);
}

Entity::~Entity() {
    for (Component* mComponent : mComponents)
    {
        mComponent->OnFree();
        mComponent->Invalidate();
    }
    mComponents.clear();
}

void Entity::RemoveComponent(Component *t) {
    auto loc = std::find(mComponents.begin(), mComponents.end(), t);
    if (loc == mComponents.end()) return;
    mComponents.erase(loc);
    t->Invalidate();
}
