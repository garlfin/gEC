//
// Created by scion on 9/7/2022.
//

#include "Component.h"
#include "Entity.h"

Component::Component(Entity& owner, uint64_t typeID) : mOwner(owner), TypeID(typeID)
{
}

const Entity *Component::Owner() {
    return &mOwner;
}

const Window *Component::Window() {
    return mOwner.Window();
}
