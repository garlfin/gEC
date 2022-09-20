//
// Created by scion on 9/3/2022.
//

#ifndef IME_TEXTURE2D_H
#define IME_TEXTURE2D_H


#include "Texture.h"

class Texture2D : public Texture {
public:
    Texture2D(Window* window, const char*, bool = false);
    Texture2D(Window* window, glm::u16vec2, GLenum, uint8_t = 0);
};

#endif //IME_TEXTURE2D_H
