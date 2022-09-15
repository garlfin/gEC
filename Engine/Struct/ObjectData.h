//
// Created by scion on 9/14/2022.
//

#ifndef IME_OBJECTDATA_H
#define IME_OBJECTDATA_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

struct ObjectData {
    glm::mat4 Model[100];
    glm::vec4 Transparency[25];
};

#endif //IME_OBJECTDATA_H
