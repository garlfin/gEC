//
// Created by scion on 9/20/2022.
//

#ifndef IME_TEXTURECUBE_H
#define IME_TEXTURECUBE_H


#include "Texture.h"

class TextureCube : public Texture {
public:
    TextureCube(class Window *window, const char *const path, bool genMips);
    TextureCube(class Window*, uint32_t, GLenum, uint8_t = 0);
};


#endif //IME_TEXTURECUBE_H
