//
// Created by scion on 9/1/2022.
//

#ifndef IME_VAO_H
#define IME_VAO_H

#include "../Asset.h"
#include "../GLBuffer.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

class VAO : public Asset {
public:
    explicit VAO(const class Window* window);
    ~VAO() override;

    virtual void Draw(uint32_t count) const = 0;
};

#endif //IME_VAO_H
