//
// Created by scion on 9/2/2022.
//

#include "Shader.h"
#include "SubShader.h"


Shader::Shader(Window &window, const char* vertex, const char* fragment) : Asset(window)
{
    SubShader vert(window, vertex, ShaderType::Vertex);
    SubShader frag(window, fragment, ShaderType::Fragment);

    _ID = glCreateProgram();

    glAttachShader(_ID, vert.id());
    glAttachShader(_ID, frag.id());

    glLinkProgram(_ID);

    vert.Free();
    frag.Free();
}

Shader::Shader(Window &window, const char* compute) : Asset(window)
{
    SubShader comp(window, compute, ShaderType::Compute);

    _ID = glCreateProgram();

    glAttachShader(_ID, comp.id());

    glLinkProgram(_ID);

    comp.Free();
}

void Shader::Use() {
    glUseProgram(_ID);
}

void Shader::Free() {
    glDeleteProgram(_ID);
}

