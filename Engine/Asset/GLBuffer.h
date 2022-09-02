//
// Created by scion on 8/31/2022.
//

#ifndef IME_GLBUFFER_H
#define IME_GLBUFFER_H

#include "glad/glad.h"
#include "Asset.h"


enum BufferBindLocation {
    UniformBuffer = GL_UNIFORM_BUFFER,
    ShaderStorage = GL_SHADER_STORAGE_BUFFER
};

template<typename T>
struct GLBuffer : public Asset {
private:
    uint32_t _count;
    uint32_t _size;
public:
    GLBuffer(Window& window, uint32_t count = 0) : Asset(window), _count(count), _size(sizeof(T) * count)
    {
        glCreateBuffers(1, &_ID);
        glNamedBufferStorage(_ID, _size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    }

    GLBuffer(Window& window, uint32_t count, T* data) : Asset(window), _count(count), _size(sizeof(T) * count)
    {
        glCreateBuffers(1, (GLuint*) &_ID);
        glNamedBufferStorage(_ID, _size, data, GL_DYNAMIC_STORAGE_BIT);
    }

    void ReplaceData(T* data, uint32_t count = -1, uint32_t offset = 0) {
        glNamedBufferSubData(_ID, offset, count == -1 ? _size : count * sizeof(T), data);
    }

    void ReplaceData(std::vector<T>* data, uint32_t offset = 0) {
        glNamedBufferSubData(_ID, offset, data->size(), data->data());
    }

    void Bind(uint32_t slot, BufferBindLocation bindLocation) {
        glBindBufferBase(bindLocation, slot, _ID);
    }

    void Free() override {
        glDeleteBuffers(1, (GLuint*) &_ID);
    }
};


#endif //IME_GLBUFFER_H
