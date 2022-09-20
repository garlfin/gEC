//
// Created by scion on 9/7/2022.
//

#include "Component.h"
#include "../Entity.h"

Component::Component(Entity* owner, const std::type_info& typeID) : _Owner(owner), TypeID(typeID.hash_code())
{
}

Entity * const Component::Owner() {
    return _Owner;
}

 Window * const Component::Window() {
    return _Owner->Window();
}

Component::~Component() { }
