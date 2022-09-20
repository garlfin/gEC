//
// Created by scion on 9/5/2022.
//

#include "Entity.h"

Entity::Entity(class Window *window, Entity *parent) : window(window), parent(parent)
{
}

void Entity::AddComponent(Component *component)
{
    components.push_back(component);
}

Entity::~Entity()
{
    for (Component *mComponent: components)
    {
        if (mComponent->Owner())
        {
            mComponent->OnFree();
            mComponent->Invalidate();
        }
        delete mComponent;
    }
    components.clear();
}

void Entity::RemoveComponent(Component *t)
{
    auto loc = std::find(components.begin(), components.end(), t);
    if (loc == components.end()) return;
    components.erase(loc);
    t->Invalidate();
}
