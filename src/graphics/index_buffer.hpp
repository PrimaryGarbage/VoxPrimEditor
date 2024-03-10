#ifndef __INDEX_BUFFER_HPP__
#define __INDEX_BUFFER_HPP__

#include "typedefs.hpp"

namespace prim
{
    class IndexBuffer
    {
    private:
        u32 glId;
        u32 count;

    public:
        IndexBuffer(const u32* data, u32 count);
        IndexBuffer(IndexBuffer&& rhs);
        IndexBuffer& operator=(IndexBuffer&& rhs);
        ~IndexBuffer();

        void bind() const noexcept;
        void unbind() const noexcept;
        u32 getCount() const noexcept;
    };
}

#endif // __INDEX_BUFFER_HPP__