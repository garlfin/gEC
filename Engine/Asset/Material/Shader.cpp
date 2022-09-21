//
// Created by scion on 9/2/2022.
//

#include "Shader.h"
#include "SubShader.h"
#include "ShaderManager.h"

Shader::Shader(class Window* window, const char* vertex, const char* fragment, ShaderManager* sMan) : Asset(window)
{
    SubShader vert(window, vertex, ShaderType::Vertex, sMan);
    SubShader frag(window, fragment, ShaderType::Fragment, sMan);

    ID = glCreateProgram();

    glAttachShader(ID, vert.Id());
    glAttachShader(ID, frag.Id());

    glLinkProgram(ID);
}

Shader::Shader(class Window* window, const char* compute, ShaderManager* sMan) : Asset(window)
{
    SubShader comp(window, compute, ShaderType::Compute, sMan);

    ID = glCreateProgram();

    glAttachShader(ID, comp.Id());

    glLinkProgram(ID);
}

void Shader::Use() const {
    glUseProgram(ID);
}


void Shader::SetUniform(uint32_t slot, const uint64_t value) const
{
    glProgramUniform2uiv(ID, slot, 1, (GLuint*) &value);
}

void Shader::SetUniform(uint32_t slot, int32_t value) const
{
    glProgramUniform1i(ID, slot, value);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

