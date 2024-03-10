#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__

#include "typedefs.hpp"
#include "vertex_buffer_layout.hpp"

namespace prim
{
    class VertexBuffer
    {
    private:
        u32 glId;
        VertexBufferLayout layout;
    public:
        VertexBuffer(const void* data, u32 size, VertexBufferLayout layout);
        VertexBuffer(VertexBuffer&& rhs);
        VertexBuffer& operator=(VertexBuffer&& rhs);
        ~VertexBuffer();

        void bind() const noexcept;
        void unbind() const noexcept;
    };
}

#endif // __VERTEX_BUFFER_HPP__