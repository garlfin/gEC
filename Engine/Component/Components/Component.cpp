//
// Created by scion on 9/7/2022.
//

#include "Component.h"
#include "../Entity.h"

Component::Component(Entity* owner, const std::type_info& typeID) : mOwner(owner), TypeID(typeID.hash_code())
{
}

Entity * const Component::Owner() {
    return mOwner;
}

 Window * const Component::Window() {
    return mOwner->Window();
}

Component::~Component() { }
