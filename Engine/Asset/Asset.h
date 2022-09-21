//
// Created by scion on 8/29/2022.
//

#ifndef IME_ASSET_H
#define IME_ASSET_H

#include <cstdint>

class Window;

class Asset {
protected:
    Asset(const Window* window) : Window(window) {  }

    const Window* Window;
    std::uint32_t ID;
public:
    Asset(const Asset&) = delete;
    Asset& operator= (const Asset&) = delete;

    virtual ~Asset() { }

    const std::int32_t Id() const { return ID; }
};


#endif //IME_ASSET_H
