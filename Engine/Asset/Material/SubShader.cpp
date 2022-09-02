//
// Created by scion on 9/1/2022.
//

#include "SubShader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

SubShader::SubShader(Window& window, const char* filePath, ShaderType type) : Asset(window)
{
    _ID = glCreateShader((GLenum) type);

    std::ifstream shaderSource;
    std::stringstream fileData;


    shaderSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderSource.open(filePath);
        fileData << shaderSource.rdbuf();
    } catch(std::ifstream ::failure exception) {
        std::cout << "Shader read failure: " << exception.what() << std::endl;
    }

    auto finalString = fileData.str();
    const char* string = finalString.c_str();
    //const char* finalString = fileString.c_str();

    glShaderSource(_ID, 1, &string, nullptr);
    glCompileShader(_ID);

    int status;
    glGetShaderiv(_ID, GL_COMPILE_STATUS, &status);
    if(!status) {
        char shaderLog[512];
        glGetShaderInfoLog(_ID, sizeof(shaderLog), nullptr, (GLchar*) &shaderLog);
        std::cout << "Shader Compile Error! \n" << shaderLog << std::endl;
    }

    shaderSource.close();


}

void SubShader::Free() {
    glDeleteShader(_ID);
}
