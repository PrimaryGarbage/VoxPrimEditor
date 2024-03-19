#ifndef __VERTEX_BUFFER_LAYOUT_HPP__
#define __VERTEX_BUFFER_LAYOUT_HPP__

#include "typedefs.hpp"
#include "glm/glm.hpp"
#include <vector>

namespace prim
{
    struct VertexAttributeLayout
    {
        glenum glType;
        u16 size;
        u8 componentCount;
        bool normalized;

        VertexAttributeLayout(glenum glType, u16 size, u8 componentCount, bool normalized)
            : glType(glType), size(size), componentCount(componentCount), normalized(normalized) {}
    };

    class VertexBufferLayout
    {
    private:
        size_t stride{0u};
        std::vector<VertexAttributeLayout> attributes;
    public:
        VertexBufferLayout& pushFloat(bool normalize = false) noexcept;
        VertexBufferLayout& pushInt(bool normalize = false) noexcept;
        VertexBufferLayout& pushUint(bool normalize = false) noexcept;
        VertexBufferLayout& pushVec2(bool normalize = false) noexcept;
        VertexBufferLayout& pushVec3(bool normalize = false) noexcept;
        VertexBufferLayout& pushVec4(bool normalize = false) noexcept;
        VertexBufferLayout& pushiVec2(bool normalize = false) noexcept;
        VertexBufferLayout& pushiVec3(bool normalize = false) noexcept;
        VertexBufferLayout& pushiVec4(bool normalize = false) noexcept;
        VertexBufferLayout& pushuVec2(bool normalize = false) noexcept;
        VertexBufferLayout& pushuVec3(bool normalize = false) noexcept;
        VertexBufferLayout& pushuVec4(bool normalize = false) noexcept;

        void bind() const noexcept;
    };
}

#endif // __VERTEX_BUFFER_LAYOUT_HPP__