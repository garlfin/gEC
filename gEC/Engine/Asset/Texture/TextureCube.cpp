//
// Created by scion on 9/20/2022.
//

#include <fstream>
#include "TextureCube.h"
#include <Struct/PVR.h>
#include <Misc/Math.h>


TextureCube::TextureCube(class Window* window, uint32_t size, GLenum format, uint8_t mips) : Texture(window)
{
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &ID);
    glTextureStorage3D(ID, MipCount(), format, size, size, 6);
}

TextureCube::TextureCube(class Window *window, const char *const path, bool genMips) : Texture(window)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) FileError(path);

    const PVR::Header *const header = PVR::LoadHeader(file);

    Size = header->Size();
    GLenum format = ToInternalFormat(header->Format);

    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &ID);
    glTextureStorage2D(ID, MipCount(), format, header->Width, header->Height);

    glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_MAX_ANISOTROPY, 4);

    glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    file.seekg(header->MetaSize, std::ifstream::cur);

    auto mipData = malloc(QUICK_CEIL_DIVISION(header->Width * header->Height, 16) * 16); // The mips won't ever be bigger than the last.
    if (!mipData) throw std::runtime_error("Failed to allocate memory for image.");

    for (int i = 0; i < header->Mips ; i++)
    {
        glm::u16vec2 mipSize = SizeAtMip(i);
        uint32_t bytesAtMip = QUICK_CEIL_DIVISION(mipSize.x * mipSize.y, 16) * 16;

        for (int x = 0; x < 6; x++)
        {
            file.read((char*) mipData, bytesAtMip);
            glCompressedTextureSubImage3D(ID, i, 0, 0, x, mipSize.x, mipSize.y, 1, format, bytesAtMip, mipData);
        }
    }
    free(mipData);

    if(genMips && header->Mips > 1) glGenerateTextureMipmap(ID);

    delete header;
}
