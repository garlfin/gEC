//
// Created by scion on 9/5/2022.
//

#ifndef IME_COMPONENT_H
#define IME_COMPONENT_H

#include <memory>

class Entity;

class Component {
private:
    std::shared_ptr<Entity> _Owner;
protected:
    Component(std::shared_ptr<Entity> &owner) {_Owner = owner; }
    Entity* Owner() { return _Owner.get(); }
public:
    void OnUpdate(double delta);
    void OnRender(double delta);
};


#endif //IME_COMPONENT_H
