#include "index_buffer.hpp"
#include "external/glad.h"
#include "opengl_utils.hpp"

namespace prim
{
    IndexBuffer::IndexBuffer(const u32* data, u32 count) : count(count)
    {
        glCall(glGenBuffers(1, &glId));
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glId));
        glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), data, GL_STATIC_DRAW));
    }
    
    IndexBuffer::IndexBuffer(IndexBuffer&& rhs) : glId(rhs.glId), count(rhs.count)
    {
        rhs.glId = 0u;
        rhs.count = 0u;
    }
    
    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& rhs)
    {
        this->~IndexBuffer();
        glId = rhs.glId;
        rhs.glId = 0u;
        count = rhs.count;
        rhs.count = 0u;

        return *this;
    }
    
    IndexBuffer::~IndexBuffer()
    {
        if(glId != 0) 
        {
            glCall(glDeleteBuffers(1, &glId));
            Logger::inst().logInfo("IndexBuffer deleted. GL ID: {0}", glId);
        }
    }
    
    void IndexBuffer::bind() const noexcept
    {
        if(glId == 0) return;
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glId));
    }
    
    void IndexBuffer::unbind() const noexcept
    {
        if(glId == 0) return;
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    u32 IndexBuffer::getCount() const noexcept
    {
        return count;
    }
}