//
// Created by scion on 9/2/2022.
//

#include "Shader.h"
#include "SubShader.h"
#include "ShaderManager.h"

Shader::Shader(Window* window, const char* vertex, const char* fragment, ShaderManager* sMan) : Asset(window)
{
    SubShader vert(window, vertex, ShaderType::Vertex, sMan);
    SubShader frag(window, fragment, ShaderType::Fragment, sMan);

    _ID = glCreateProgram();

    glAttachShader(_ID, vert.id());
    glAttachShader(_ID, frag.id());

    glLinkProgram(_ID);
}

Shader::Shader(Window* window, const char* compute, ShaderManager* sMan) : Asset(window)
{
    SubShader comp(window, compute, ShaderType::Compute, sMan);

    _ID = glCreateProgram();

    glAttachShader(_ID, comp.id());

    glLinkProgram(_ID);
}

void Shader::Use() const {
    glUseProgram(_ID);
}


void Shader::SetUniform(uint32_t slot, const uint64_t value) const
{
    glProgramUniform2uiv(_ID, slot, 1, (GLuint*) &value);
}

void Shader::SetUniform(uint32_t slot, int32_t value) const
{
    glProgramUniform1i(_ID, slot, value);
}

Shader::~Shader() {
    glDeleteProgram(_ID);
}

