//
// Created by scion on 9/3/2022.
//

#define quickCeilDivision(x, y) (((x) + (y) - 1) / (y))

#include <fstream>
#include "Texture2D.h"
#include "../../Struct/PVR.h"
#include <iostream>


Texture2D::Texture2D(Window* window, const char *path, bool genMips ) : Texture(window)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file");
    }

    const PVR::Header *const header = PVR::LoadHeader(file);

    Size = header->Size();
    mMipCount = header->Mips;

    GLenum format = ToInternalFormat(header->Format);

    if(header->ColorSpace == 1) format += 2140;

    glCreateTextures(GL_TEXTURE_2D, 1, &_ID);
    glTextureStorage2D(_ID, header->Mips, format, header->Width, header->Height);

    glTextureParameteri(_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(_ID, GL_TEXTURE_MAX_ANISOTROPY, 4);

    glTextureParameteri(_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    file.seekg(header->MetaSize, std::ifstream::cur);

    for (int i = 0; i < header->Mips ; i++)
    {
        glm::u16vec2 mipSize = SizeAtMip(i);
        uint32_t bytesAtMip = quickCeilDivision(mipSize.x * mipSize.y, 16) * 16;

        auto mipData = malloc(bytesAtMip);
        if(mipData == nullptr) throw std::runtime_error("Failed to allocate memory for image.");
        file.read((char*) mipData, bytesAtMip);

        glCompressedTextureSubImage2D(_ID, i, 0, 0, mipSize.x, mipSize.y, format, bytesAtMip, mipData);
        free(mipData);
    }

    if(genMips || header->Mips == 1) glGenerateTextureMipmap(_ID);

    delete header;
}

Texture2D::Texture2D(Window *window, const glm::u16vec2 size, const GLenum format, uint8_t mips) : Texture(window)
{
    Size = size;
    mips = mips;

    glCreateTextures(GL_TEXTURE_2D, 1, &_ID);
    glTextureStorage2D(mips, MipCount(), format, Size.x, Size.y);

    glTextureParameteri(_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(_ID, GL_TEXTURE_MAX_ANISOTROPY, 4);

    glTextureParameteri(_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
