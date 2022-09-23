//
// Created by scion on 9/12/2022.
//

#include <fstream>
#include "ShaderManager.h"


ShaderManager::ShaderManager() : AssetManager<Shader>(), Includes() {

}

void ShaderManager::AddInclude(const char *const filePath)
{
    std::ifstream shaderSource(filePath, std::ios::in | std::ios::binary);

    shaderSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    shaderSource.seekg(0, shaderSource.end);
    int32_t bytesToRead = shaderSource.tellg();

    char* sPtr = new char[bytesToRead + 1] {};
    shaderSource.seekg(0, shaderSource.beg);
    shaderSource.read(sPtr, bytesToRead);

    Includes.emplace_back(filePath, sPtr);

    shaderSource.close();
}

ShaderManager::~ShaderManager() {
    for(int i = 0; i < Includes.size(); i++) {
        delete[] Includes.at(i).Source;
    }
}
