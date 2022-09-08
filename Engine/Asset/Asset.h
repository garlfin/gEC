//
// Created by scion on 8/29/2022.
//

#ifndef IME_ASSET_H
#define IME_ASSET_H

#include <cstdint>

class Window;

class Asset {
protected:
    const Window* _Window;
    std::uint32_t _ID;
    Asset(const Window* window) : _Window(window) {  }
    bool _disposed;
    virtual void Dispose() = 0;
public:
    void Free() { if(_disposed) return; _disposed = true; Dispose(); };
    const std::int32_t id() const { return _ID; }
    virtual ~Asset(){ Free(); }

    Asset(const Asset&) = delete;
    Asset& operator= (const Asset&) = delete;
};


#endif //IME_ASSET_H
