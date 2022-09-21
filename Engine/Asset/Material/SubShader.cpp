//
// Created by scion on 9/1/2022.
//

#include "SubShader.h"
#include "ShaderManager.h"
#include <cstring>
#include <iostream>
#include <fstream>

SubShader::SubShader(class Window *window, const char *filePath, ShaderType type, ShaderManager *sManager) : Asset(window)
{
    ID = glCreateShader((GLenum) type);

    std::ifstream shaderSource(filePath, std::ios::in | std::ios::binary);

    if(!shaderSource.is_open()) throw std::runtime_error("File failed to open");

    shaderSource.seekg(0, shaderSource.end);
    int32_t bytesToRead = shaderSource.tellg();

    char* sPtr = new char[bytesToRead + 1] {};

    shaderSource.seekg(0, shaderSource.beg);
    shaderSource.read(sPtr, bytesToRead);

    // Home-grown include system
    // I hate all this nesting...
    if (sManager != nullptr)
    {
        while (true) {
            char* locatedInclude = std::strstr(sPtr, "#include \"");

            if (locatedInclude == nullptr) break;

            for (int i = 0; i < sManager->Includes.size(); i++)
            {
                const char* const incPath = sManager->Includes.at(i).Name;
                const char* const incData = sManager->Includes.at(i).Source;

                bool isSame = true;

                // Compare strings
                // First iteration: Check if length matches up
                if(*(locatedInclude + 10 + strlen(incPath)) != '"') continue;
                // Second iteration: repeat for all characters, compare. If not some, mark wrong.
                for(int c = 0; c < strlen(incPath); c++)
                    if(*(locatedInclude + 10 + c) != *(incPath + c)) { isSame = false; break; }

                if (!isSame) continue;

                int afterDirectiveBCount = (sPtr + bytesToRead) - (locatedInclude + 11 + strlen(incPath));
                bytesToRead += strlen(incData) - 11 - strlen(incPath); // is the Length of #include ""

                char* const newStr = (char*) calloc(bytesToRead + 1, 1);

                memcpy(newStr, sPtr, locatedInclude - sPtr); // Data before include
                memcpy(newStr + (locatedInclude - sPtr), incData, strlen(incData)); // Data at include
                memcpy(newStr + (locatedInclude - sPtr) + strlen(incData), sPtr + (locatedInclude - sPtr) + 11 + strlen(incPath), afterDirectiveBCount);

                free(sPtr);
                sPtr = newStr;

                break;
            }
        }
    }


    glShaderSource(ID, 1, &sPtr, nullptr);

    free(sPtr);

    glCompileShader(ID);

    int status;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &status);
    if(!status)
    {
        int logLen;
        glGetShaderiv(Id(), GL_INFO_LOG_LENGTH, &logLen);

        char* const shaderLog = new char[logLen];
        glGetShaderInfoLog(ID, logLen, nullptr, shaderLog);
        std::cout << " Shader Compile Error! \n" << shaderLog << std::endl;
        std::cout << "Shader source: " << *sPtr << std::endl;
        delete[] shaderLog;
    }

    shaderSource.close();
}

SubShader::~SubShader() {
    glDeleteShader(ID);
}
