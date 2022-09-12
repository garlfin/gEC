//
// Created by scion on 8/29/2022.
//

#ifndef IME_ASSET_H
#define IME_ASSET_H

#include <cstdint>

class Window;

class Asset {
protected:
    Asset(const Window* window) : _Window(window) {  }

    const Window* _Window;
    std::uint32_t _ID;
public:
    Asset(const Asset&) = delete;
    Asset& operator= (const Asset&) = delete;

    virtual ~Asset() { }

    const std::int32_t id() const { return _ID; }
};


#endif //IME_ASSET_H
