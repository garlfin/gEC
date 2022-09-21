//
// Created by scion on 9/2/2022.
//

#ifndef IME_SHADER_H
#define IME_SHADER_H

#include <string>
#include "../Asset.h"
#include <glm/vec2.hpp>

class ShaderManager;

class Shader : public Asset {
public:
    Shader(class Window* window, const char*, const char*, ShaderManager* = nullptr); // Vertex, Fragment
    Shader(class Window* window, const char*, ShaderManager* = nullptr); // Compute

    ~Shader();

    void Use() const;

    void SetUniform(uint32_t, uint64_t) const;
    void SetUniform(uint32_t slot, int32_t value) const;
};




#endif //IME_SHADER_H
