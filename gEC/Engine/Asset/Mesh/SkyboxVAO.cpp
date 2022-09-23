//
// Created by scion on 9/21/2022.
//

#include "SkyboxVAO.h"

namespace {
    const float SkyboxVertices[]
    {
        -1, -1, -1,
        1, -1, -1,
        1, 1, -1,
        -1, 1, -1,
        -1, -1, 1,
        1, -1, 1,
        1, 1, 1,
        -1, 1, 1
    };

    const uint32_t SkyboxIndices[]
    {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        0, 4, 7,
        7, 3, 0,
        1, 5, 6,
        6, 2, 1,
        0, 1, 5,
        5, 4, 0,
        3, 2, 6,
        7, 6, 3
    };
}


SkyboxVAO::SkyboxVAO(const class Window * window) : VAO(window), positions(window, 8, (glm::vec3*) &SkyboxVertices), indices(window, 24, (glm::uvec3*) &SkyboxIndices)
{
    glVertexArrayVertexBuffer(ID, 0, positions.Id(), 0, sizeof(glm::vec3));

    glEnableVertexArrayAttrib(ID, 0);

    glVertexArrayAttribFormat(ID, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(ID, 0, 0);
    glVertexArrayElementBuffer(ID, indices.Id());
}

void SkyboxVAO::Draw(uint32_t count) const
{
    glBindVertexArray(ID);
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr, count);
}
