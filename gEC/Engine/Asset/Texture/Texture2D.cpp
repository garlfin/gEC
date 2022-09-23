//
// Created by scion on 9/3/2022.
//
#include <fstream>
#include <Struct/PVR.h>
#include <iostream>
#include <Misc/Math.h>
#include "Texture2D.h"

Texture2D::Texture2D(class Window* window, const char *path, bool genMips) : Texture(window)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) FileError(path);


    const PVR::Header *const header = PVR::LoadHeader(file);

    Size = header->Size();
    mMipCount = header->Mips;

    GLenum format = ToInternalFormat(header->Format);

    if(header->ColorSpace == 1) format += 2140;

    glCreateTextures(GL_TEXTURE_2D, 1, &ID);
    glTextureStorage2D(ID, header->Mips, format, header->Width, header->Height);

    glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_MAX_ANISOTROPY, 4);

    glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    file.seekg(header->MetaSize, std::ifstream::cur);

    auto mipData = malloc(QUICK_CEIL_DIVISION(header->Width * header->Height, 16) * 16);
    if(!mipData) throw std::runtime_error("Failed to allocate memory for image."); // Mips always smaller than the last
    // Why allocate multiple times?

    for (int i = 0; i < header->Mips ; i++)
    {
        glm::u16vec2 mipSize = SizeAtMip(i);
        uint32_t bytesAtMip = QUICK_CEIL_DIVISION(mipSize.x * mipSize.y, 16) * 16;

        file.read((char*) mipData, bytesAtMip);

        glCompressedTextureSubImage2D(ID, i, 0, 0, mipSize.x, mipSize.y, format, bytesAtMip, mipData);
    }
    free(mipData);

    if(genMips && header->Mips > 1) glGenerateTextureMipmap(ID);

    delete header;
}

Texture2D::Texture2D(class Window *window, const glm::u16vec2 size, const GLenum format, uint8_t mips) : Texture(window)
{
    Size = size;
    mips = mips;

    glCreateTextures(GL_TEXTURE_2D, 1, &ID);
    glTextureStorage2D(mips, MipCount(), format, Size.x, Size.y);

    glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_MAX_ANISOTROPY, 4);

    glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
