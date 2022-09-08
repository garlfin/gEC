//
// Created by scion on 9/1/2022.
//

#ifndef IME_VAO_H
#define IME_VAO_H

#include "../Asset.h"
#include "../GLBuffer.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

struct VAO : public Asset {
private:
    GLBuffer<glm::vec3> positions;
    GLBuffer<glm::uvec3> indices;
protected:
    void Dispose() override;
public:
    VAO(const Window* window);
    void Draw(uint32_t count) const;
};

#endif //IME_VAO_H
