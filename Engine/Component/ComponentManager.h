//
// Created by scion on 9/7/2022.
//

#ifndef IME_COMPONENTMANAGER_H
#define IME_COMPONENTMANAGER_H

#include <vector>
#include <iostream>
#include "Component.h"

template<typename T>
class ComponentManager {
    std::vector<T*> components;
    std::vector<T*> initQueue;

public:
    ComponentManager() : components(), initQueue() {
        static_assert(std::is_base_of<Component, T>::value, "Component manager must manage an inheritor of Component");
    }

    template<typename ... Args>
    T* Create(Args&& ... args)
    {
        T* ptr = new T(std::forward<Args>(args)...);
        components.push_back(ptr);
        initQueue.push_back(ptr);
        return components.at(components.size() - 1);
    }

    void OnRender(double delta) { for (T* component : components) component->OnRender(delta); }
    void OnUpdate(double delta)
    {
        for (T* component : initQueue) { component->OnLoad(); }
        initQueue.clear();
        for (T* component : components) { component->OnUpdate(delta); }
    }
    void Free(T* object)
    {
        if(!std::count(components.begin(), components.end(), object))
        {
            std::cout << "Attempt to delete non-managed Component" << std::endl;
            return;
        }

        object->OnFree();
        std::remove(components.begin(), components.end(), object);
        delete object;
    }
};


#endif //IME_COMPONENTMANAGER_H
