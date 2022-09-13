//
// Created by scion on 9/1/2022.
//

#ifndef IME_SUBSHADER_H
#define IME_SUBSHADER_H

#include <glad/glad.h>
#include <string>
#include "../Asset.h"
#include "ShaderManager.h"

enum class ShaderType {
    Fragment = GL_FRAGMENT_SHADER,
    Vertex = GL_VERTEX_SHADER,
    Compute = GL_COMPUTE_SHADER
};

class SubShader : public Asset {
public:
    SubShader(Window *window, const char *filePath, ShaderType type, ShaderManager *sManager);
    ~SubShader();
};


#endif //IME_SUBSHADER_H
