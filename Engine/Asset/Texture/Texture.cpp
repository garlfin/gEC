//
// Created by scion on 9/3/2022.
//

#include "Texture.h"
#include "math.h"

Texture::Texture(Window* window) : Asset(window), _handle(0), mMipCount(0) {}

const glm::uvec2 Texture::size() const { return Size; }

const uint64_t Texture::handle() {
    if (_handle == 0)
    {
        _handle = glGetTextureHandleARB(_ID);
        glMakeTextureHandleResidentARB(_handle);
    }
    return _handle;
}

uint8_t Texture::MipCount() {
    if (mMipCount != 0) return mMipCount;
    mMipCount = log2(std::min(Size.x, Size.y)) + 1;
    return mMipCount;
}

const glm::u16vec2 Texture::SizeAtMip(const uint16_t level) const {
    return glm::u16vec2(Size.x >> level, Size.y >> level);
}

const int32_t Texture::Use(int32_t slot) const {
    glBindTextureUnit(slot, _ID);
    return slot;
}

Texture::~Texture() {
    if(_handle != 0) glMakeTextureHandleNonResidentARB(_handle);
    glDeleteTextures(1, &_ID);
}

#define PVR_BC1 7
#define PVR_BC2 9
#define PVR_BC3 11

const GLenum Texture::ToInternalFormat(uint32_t format) {
    switch(format) {
        case PVR_BC1: return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        case PVR_BC2: return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        case PVR_BC3: return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        case 12: return GL_COMPRESSED_RED_RGTC1;
        case 13: return GL_COMPRESSED_RG_RGTC2;
        default: return 0;
    }
}

