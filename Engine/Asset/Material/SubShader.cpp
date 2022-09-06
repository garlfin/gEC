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

    std::ifstream shaderSource(filePath, std::ios::in | std::ios::binary);

    shaderSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    shaderSource.seekg(0, shaderSource.end);
    int32_t bytesToRead = shaderSource.tellg();

    char* sPtr = new char[bytesToRead];
    shaderSource.seekg(0, shaderSource.beg);
    shaderSource.read(sPtr, bytesToRead);

    glShaderSource(_ID, 1, &sPtr, &bytesToRead);

    delete[] sPtr;

    glCompileShader(_ID);

    int status;
    glGetShaderiv(_ID, GL_COMPILE_STATUS, &status);
    if(!status)
    {
        int logLen;
        glGetShaderiv(id(), GL_INFO_LOG_LENGTH, &logLen);

        char shaderLog[logLen];
        glGetShaderInfoLog(_ID, sizeof(shaderLog), nullptr, (GLchar *) &shaderLog);
        std::cout << " Shader Compile Error! \n" << shaderLog << std::endl;
    }


    shaderSource.close();


}

void SubShader::Dispose() {
    glDeleteShader(_ID);
}
