//
// Created by scion on 9/21/2022.
//

#pragma once

#include "VAO.h"

class SkyboxVAO : public VAO
{
private:
    GLBuffer<glm::vec3> positions;
    GLBuffer<glm::uvec3> indices;

public:
    explicit SkyboxVAO(const class Window*);

    void Draw(uint32_t count) const override;
};
