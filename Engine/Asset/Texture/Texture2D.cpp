//
// Created by scion on 9/3/2022.
//

#define quickCeilDivision(x, y) (((x) + (y) - 1) / (y))

#include <fstream>
#include "Texture2D.h"
#include "../../Struct/PVRHeader.h"
#include <iostream>

Texture2D::Texture2D(Window* window, const char *path, bool genMips ) : Texture(window)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::string errMsg = "Failed to load file: " + static_cast<std::string>(path);
        throw std::runtime_error(errMsg);
    }

    PVRHeader pvrHeader;

    file.read((char*) &pvrHeader, sizeof(PVRHeader));
    file.seekg(pvrHeader.MetaSize, std::ios::cur);

    _size = glm::u16vec2(pvrHeader.Width, pvrHeader.Height);

    GLenum format = ToInternalFormat(pvrHeader.Format);

    if(pvrHeader.ColorSpace == 1) format += 2140;

    if(pvrHeader.Version == 0x50565203) std::cout << "Endianness does not match" << std::endl;

    glCreateTextures(GL_TEXTURE_2D, 1, (GLuint*) &_ID);
    glTextureStorage2D(_ID, pvrHeader.Mips, format, pvrHeader.Width, pvrHeader.Height);

    glTextureParameteri(_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(_ID, GL_TEXTURE_MAX_ANISOTROPY, 4);

    glTextureParameteri(_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    for (int i = 0; i < pvrHeader.Mips ; i++)
    {
        glm::u16vec2 mipSize = SizeAtMip(i);
        uint32_t bytesAtMip = quickCeilDivision(mipSize.x * mipSize.y, 16) * 16;

        auto mipData = malloc(bytesAtMip);
        if(mipData == nullptr) throw std::runtime_error("Failed to allocate memory for image.");
        file.read((char*) mipData, bytesAtMip);

        glCompressedTextureSubImage2D(_ID, i, 0, 0, mipSize.x, mipSize.y, format, bytesAtMip, mipData);
        free(mipData);
    }

    if(genMips || pvrHeader.Mips == 1) glGenerateTextureMipmap(_ID);


}
