//
// Created by scion on 9/3/2022.
//

#ifndef IME_TEXTURE_H
#define IME_TEXTURE_H

#include <glad/glad.h>
#include "../Asset.h"
#include <glm/vec2.hpp>

class Texture : public Asset {
private:
    uint64_t _handle;
protected:
    glm::u16vec2 _size;
    virtual void Dispose() override;
    static const GLenum ToInternalFormat(uint32_t);
public:
    Texture(Window* window);
    const glm::uvec2 size() const;
    const uint64_t handle();
    const uint16_t MipCount() const;
    const glm::u16vec2 SizeAtMip(const uint16_t) const;
    virtual const int32_t Use(int32_t slot) const;
};


#endif //IME_TEXTURE_H
