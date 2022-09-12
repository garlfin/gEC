//
// Created by scion on 9/7/2022.
//

#include "Component.h"
#include "Entity.h"

Component::Component(Entity* owner, uint64_t typeID) : mOwner(owner), TypeID(typeID)
{
}

Entity * const Component::Owner() {
    return mOwner;
}

 Window * const Component::Window() {
    return mOwner->Window();
}

Component::~Component() { }
