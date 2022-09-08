//
// Created by scion on 9/1/2022.
//

#include "VAO.h"

void VAO::Draw(uint32_t count) const {
    glBindVertexArray(_ID);
    glDrawElementsInstanced(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr, count);
}

const float triVerts[] {
    -1, -1, 0,
    0, 1, 0,
    1, -1, 0
};

const uint32_t triIndices[] {
    0, 1 , 2
};

VAO::VAO(const Window* window) : Asset(window), positions(window, 3, (glm::vec3*) &triVerts), indices(window, 3, (glm::uvec3*) &triIndices)
{
    glCreateVertexArrays(1, (GLuint*) &_ID);
    glVertexArrayVertexBuffer(_ID, 0, positions.id(), 0, sizeof(glm::vec3));

    glEnableVertexArrayAttrib(_ID, 0);

    glVertexArrayAttribFormat(_ID, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(_ID, 0, 0);
    glVertexArrayElementBuffer(_ID, indices.id());

}

void VAO::Dispose() {
    positions.Free();
    indices.Free();
    glDeleteVertexArrays(1, (GLuint*) &_ID);
}
