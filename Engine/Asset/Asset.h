//
// Created by scion on 8/29/2022.
//

#ifndef IME_ASSET_H
#define IME_ASSET_H

#include <cstdint>
#include "AssetManager.h"
class Window;

class Asset {
protected:
    Window* _Window;
    std::int32_t _ID;
    Asset(Window& window) : _Window(&window) {  }
public:
    virtual void Free() = 0;
    const std::int32_t id() { return _ID; }
    // Asset (const Asset&) = delete;
    // Asset& operator= (const Asset&) = delete;
};


#endif //IME_ASSET_H
