//
// Created by scion on 9/12/2022.
//

#ifndef IME_SHADERMANAGER_H
#define IME_SHADERMANAGER_H

#include <vector>
#include "../../Windowing/Window.h"
#include "../AssetManager.h"
#include "Shader.h"

struct GLSLInclude {
public:
    GLSLInclude(const char* const name, const char* const source) : Name(name), Source(source) {}

    const char* const Name;
    const char* const Source;
};

class ShaderManager : public AssetManager<Shader> {
public:
    ShaderManager();
    ~ShaderManager();
    void AddInclude(const char* const filePath);

    std::vector<GLSLInclude> Includes;
};


#endif //IME_SHADERMANAGER_H
