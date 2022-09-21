//
// Created by scion on 9/1/2022.
//

#include "VAO.h"

namespace {
    const float TriVerts[]
    {
        -1, -1, 0,
        0, 1, 0,
        1, -1, 0
    };

    const uint32_t TriIndices[]
    {
        0, 1, 2
    };

    const float SkyboxVerts[]
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
        6, 2, 1
    };
}

VAO::VAO(const class Window* window) : Asset(window), positions(window, 8, (glm::vec3*) &SkyboxVerts), indices(window, 24, (glm::uvec3*) &SkyboxIndices)
{
    glCreateVertexArrays(1, (GLuint*) &ID);
    glVertexArrayVertexBuffer(ID, 0, positions.Id(), 0, sizeof(glm::vec3));

    glEnableVertexArrayAttrib(ID, 0);

    glVertexArrayAttribFormat(ID, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(ID, 0, 0);
    glVertexArrayElementBuffer(ID, indices.Id());

}

void VAO::Draw(uint32_t count) const {
    glBindVertexArray(ID);
    glDrawElementsInstanced(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr, count);
}


VAO::~VAO() {
    glDeleteVertexArrays(1, (GLuint*) &ID);
}
