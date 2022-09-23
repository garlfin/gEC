//
// Created by scion on 8/29/2022.
//

#pragma once

#include <cstdint>
#include <stdexcept>
#include <exception>
#include <cstring>

class Window;

class Asset {
protected:
    Asset(const Window* window) : Window(window) {  }

    const Window* Window;
    std::uint32_t ID;

    static void FileError(const char* const file)
    {
        char* err = new char[100] {"Couldn't find file "};
        throw std::runtime_error(strncat(err, file, strlen(file)));
    };
public:
    Asset(const Asset&) = delete;
    Asset& operator= (const Asset&) = delete;

    virtual ~Asset() { }

    const std::int32_t Id() const { return ID; }
};


