//
// Created by scion on 9/20/2022.
//

#include "TextureCube.h"


TextureCube::TextureCube(Window* window, uint32_t size, GLenum format, uint8_t mips) : Texture(window)
{
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &_ID);
    glTextureStorage3D(_ID, MipCount(), format, size, size, 6);
}

TextureCube::TextureCube(Window *window, const char *const path) : Texture(window) {
}
