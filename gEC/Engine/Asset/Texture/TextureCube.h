//
// Created by scion on 9/20/2022.
//

#pragma once


#include "Texture.h"

class TextureCube : public Texture {
public:
    TextureCube(class Window *window, const char *path, bool genMips = true);
    TextureCube(class Window*, uint32_t, GLenum, uint8_t = 0);

};


