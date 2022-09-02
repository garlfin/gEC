//
// Created by scion on 8/30/2022.
//

#ifndef IME_ASSETMANAGER_H
#define IME_ASSETMANAGER_H

#include <vector>
#include "Asset.h"

template<typename T>
class AssetManager {
protected:
    std::vector<T> Assets;
public:
    AssetManager() : Assets() {}
    T* Register(T);

    bool Remove(T*);
    bool Free(T*);
    void Free();
};

template<typename T>
T* AssetManager<T>::Register(T t) {
    Assets.push_back(t);
    return &Assets[Assets.size() - 1];
}

template<typename T>
bool AssetManager<T>::Remove(T* t) {
    std::remove(Assets.begin(), Assets.end(), t);
    return true;
}

template<typename T>
bool AssetManager<T>::Free(T* t) {
    auto x = std::find(Assets.begin(), Assets.end(), t);
    if(x != -1) {
        Assets[x].Free();
        Assets.erase(Assets.begin() + x); // Not gonna lie I ain't got no idea how this stuff works in c++
    }
    return (x != -1);
}

template<typename T>
void AssetManager<T>::Free() {
    for(int i = 0; i < Assets.size(); i++) {
        Assets[i].Free();
    }
    Assets.clear();
}

#endif //IME_ASSETMANAGER_H
