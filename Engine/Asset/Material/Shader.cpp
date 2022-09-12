//
// Created by scion on 9/2/2022.
//

#include "Shader.h"
#include "SubShader.h"


Shader::Shader(Window* window, const char* vertex, const char* fragment) : Asset(window)
{
    SubShader vert(window, vertex, ShaderType::Vertex);
    SubShader frag(window, fragment, ShaderType::Fragment);

    _ID = glCreateProgram();

    glAttachShader(_ID, vert.id());
    glAttachShader(_ID, frag.id());

    glLinkProgram(_ID);
}

Shader::Shader(Window* window, const char* compute) : Asset(window)
{
    SubShader comp(window, compute, ShaderType::Compute);

    _ID = glCreateProgram();

    glAttachShader(_ID, comp.id());

    glLinkProgram(_ID);
}

void Shader::Use() const {
    glUseProgram(_ID);
}


void Shader::SetUniform(uint32_t slot, const uint64_t value) const
{
    glProgramUniform2ui(_ID, slot, 1, value);
}

void Shader::SetUniform(uint32_t slot, int32_t value) const
{
    glProgramUniform1i(_ID, slot, value);
}

Shader::~Shader() {
    glDeleteProgram(_ID);
}

