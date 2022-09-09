//
// Created by scion on 9/6/2022.
//

#ifndef IME_ASSETMANAGER_H
#define IME_ASSETMANAGER_H

#include <vector>

template<typename T>
class AssetManager {
    std::vector<T*> assets;
public:
    AssetManager() : assets() {
        static_assert(std::is_base_of<Asset, T>::value, "Asset manager can only manage assets");
    };

    template<typename I, typename ... Args>
    I* Create(Args&& ... args) {
        static_assert(std::is_base_of<T, I>::value, "Asset manager can only manage descendants of base T");
        I* t = new I(std::forward<Args>(args)...);
        assets.push_back(t);
        return t;
    }

    void Free() { for (unsigned int i = 0; i < assets.size(); i++) { assets.at(i)->Free(); delete assets.at(i); } assets.clear(); }
    void Free(T* object) { std::find(assets.begin(), assets.end(), object)->Free(); delete object; }

};

#endif //IME_ASSETMANAGER_H