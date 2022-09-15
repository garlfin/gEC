//
// Created by scion on 8/31/2022.
//

#ifndef IME_GLBUFFER_H
#define IME_GLBUFFER_H

#include <vector>
#include "glad/glad.h"
#include "Asset.h"


enum class BufferBindLocation {
    UniformBuffer = GL_UNIFORM_BUFFER,
    ShaderStorage = GL_SHADER_STORAGE_BUFFER
};

template<typename T>
class GLBuffer : public Asset {
private:
    uint32_t _size;
public:
    GLBuffer(const Window* window, uint32_t count = 1) : Asset(window), _size(sizeof(T) * count)
    {
        glCreateBuffers(1, (GLuint*) &_ID);
        glNamedBufferStorage(_ID, _size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    }

    ~GLBuffer() { glDeleteBuffers(1, &_ID); }

    GLBuffer(const Window* window, uint32_t count, T* data) : Asset(window), _size(sizeof(T) * count)
    {
        glCreateBuffers(1, (GLuint*) &_ID);
        glNamedBufferStorage(_ID, _size, data, GL_DYNAMIC_STORAGE_BIT);
    }

    void ReplaceData(T* data, uint32_t count = 1, uint32_t offset = 0) {
        glNamedBufferSubData(_ID, offset, count * sizeof(T), data);
    }

    void ReplaceData(std::vector<T>* data, uint32_t offset = 0) {
        glNamedBufferSubData(_ID, offset, data->size() * sizeof(T), data->data());
    }

    void ReplaceData(void* data, uint32_t byteCount = sizeof(T), uint32_t offset = 0) {
        glNamedBufferSubData(_ID, offset, byteCount, data);
    }

    void Bind(uint32_t slot, BufferBindLocation bindLocation) {
        glBindBufferBase((GLenum) bindLocation, slot, _ID);
    }
};


#endif //IME_GLBUFFER_H
