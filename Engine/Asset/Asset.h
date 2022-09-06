//
// Created by scion on 8/29/2022.
//

#ifndef IME_ASSET_H
#define IME_ASSET_H

#include <cstdint>

class Window;

class Asset {
protected:
    Window* _Window;
    std::uint32_t _ID;
    Asset(Window& window) : _Window(&window) {  }
    bool _disposed;
    virtual void Dispose() = 0;
public:
    void Free() { if(_disposed) return; _disposed = true; Dispose(); };
    const std::int32_t id() const { return _ID; }
    ~Asset(){ Free(); }
};


#endif //IME_ASSET_H
