//
// Created by scion on 9/2/2022.
//

#ifndef IME_SHADER_H
#define IME_SHADER_H


#include <string>
#include "../Asset.h"

class Shader : public Asset {
public:
    Shader(Window& window, const char*, const char*); // Vertex, Fragment
    Shader(Window& window, const char*); // Compute
    void Use();
    void Free() override;
};




#endif //IME_SHADER_H
