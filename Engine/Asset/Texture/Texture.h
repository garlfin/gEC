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
    glm::u16vec2 Size;
    uint8_t mMipCount;
    static const GLenum ToInternalFormat(uint32_t);
public:
    explicit Texture(class Window* window);
    ~Texture() override;

    virtual const int32_t Use(int32_t slot) const;

    [[nodiscard]] const glm::uvec2 size() const;
    const uint64_t handle();
    [[nodiscard]] uint8_t MipCount();
    [[nodiscard]] const glm::u16vec2 SizeAtMip(uint16_t) const;

};


#endif //IME_TEXTURE_H
