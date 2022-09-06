//
// Created by scion on 9/5/2022.
//

#ifndef IME_ENTITY_H
#define IME_ENTITY_H

#include <memory>

class Window;

class Entity {
private:
    std::shared_ptr<Entity> _parent;
protected:
    Window* Window;
public:
    Entity* Parent() { return _parent.get(); }
    void Free();
};


#endif //IME_ENTITY_H
