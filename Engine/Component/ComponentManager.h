//
// Created by scion on 9/7/2022.
//

#ifndef IME_COMPONENTMANAGER_H
#define IME_COMPONENTMANAGER_H

#include <vector>
#include <iostream>

template<typename T>
class ComponentManager {
    std::vector<T*> components;
    std::vector<T*> initQueue;

public:
    ComponentManager() : components(), initQueue() {
    }

    template<typename I, typename ... Args>
    I* Create(Args&& ... args)
    {
        I* ptr = new I(std::forward<Args>(args)...);
        components.push_back(ptr);
        initQueue.push_back(ptr);
        return ptr;
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
        auto pos = std::find(components.begin(), components.end(), object);
        if(pos == components.end())
        {
            std::cout << "Attempt to delete non-managed Component" << std::endl;
            return;
        }

        object->Free();
        components.erase(pos);
        delete object; // Problem Line
    }

    void Free() {
        for (T* component : components) { component->OnFree(); delete component; }
        components.clear();
        std::destroy(components.begin(), components.end());
    }
};


#endif //IME_COMPONENTMANAGER_H
