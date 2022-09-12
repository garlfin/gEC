//
// Created by scion on 9/1/2022.
//

#ifndef IME_SUBSHADER_H
#define IME_SUBSHADER_H

#include <glad/glad.h>
#include <string>
#include "../Asset.h"

enum class ShaderType {
    Fragment = GL_FRAGMENT_SHADER,
    Vertex = GL_VERTEX_SHADER,
    Compute = GL_COMPUTE_SHADER
};

class SubShader : public Asset {
public:
    SubShader(Window* window, const char*, ShaderType);
    ~SubShader();
};


#endif //IME_SUBSHADER_H
