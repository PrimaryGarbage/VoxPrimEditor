#include "vertex_buffer.hpp"
#include "external/glad.h"
#include "opengl_utils.hpp"

namespace prim
{
    VertexBuffer::VertexBuffer(const void* data, u32 size, VertexBufferLayout layout) : layout(layout) 
    {
        glCall(glGenBuffers(1, &glId));
        glCall(glBindBuffer(GL_ARRAY_BUFFER, glId));
        glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }
    
    VertexBuffer::VertexBuffer(VertexBuffer&& rhs) : glId(rhs.glId), layout(rhs.layout)
    {
        rhs.glId = 0u;
    }
    
    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& rhs)
    {
        this->~VertexBuffer();
        glId = rhs.glId;
        layout = rhs.layout;
        rhs.glId = 0u;

        return *this;
    }
    
    VertexBuffer::~VertexBuffer()
    {
        if(glId != 0) 
        {
            glCall(glDeleteBuffers(1, &glId));
            Logger::inst().logInfo("VertexBuffer deleted.");
        }
    }

    void VertexBuffer::bind() const noexcept
    {
        if(glId == 0) return;
        glCall(glBindBuffer(GL_ARRAY_BUFFER, glId));
        layout.bind();
    }
    
    void VertexBuffer::unbind() const noexcept
    {
        if(glId == 0) return;
        glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}