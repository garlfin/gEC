//
// Created by scion on 9/1/2022.
//

#include "VAO.h"

VAO::VAO(const class Window* window) : Asset(window)
{
    glCreateVertexArrays(1, (GLuint*) &ID);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, (GLuint*) &ID);
}
