//
// Created by scion on 9/7/2022.
//

#pragma once

#include <vector>
#include <iostream>

class Window;

template<typename T>
class ComponentManager {
private:
    std::vector<T*> components;
    std::vector<T*> initQueue;
protected:
    Window* MWindow;
public:
    explicit ComponentManager(Window* window) : MWindow(window), components(), initQueue() {}

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

        if (object->Owner()) { object->OnFree(); object->Owner()->RemoveComponent(object);  }
        components.erase(pos);
        delete object;
    }

    void Free()
    {
        for (int i = 0; i < components.size(); i++)
        {
            T* component = components.at(i);

            if (component->Owner())
            {
                component->OnFree();
                component->Owner()->RemoveComponent(component);
            }
            delete component;
        }

        components.clear();
    }
};
