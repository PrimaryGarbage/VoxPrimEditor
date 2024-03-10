#include "vertex_buffer_layout.hpp"
#include "external/glad.h"
#include "opengl_utils.hpp"

namespace prim
{
    VertexBufferLayout& VertexBufferLayout::pushFloat(bool normalize) noexcept
    {
        attributes.emplace_back(GL_FLOAT, sizeof(float), 1, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushInt(bool normalize) noexcept
    {
        attributes.emplace_back(GL_INT, sizeof(int), 1, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushUint(bool normalize) noexcept
    {
        attributes.emplace_back(GL_UNSIGNED_INT, sizeof(uint), 1, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushVec2(bool normalize) noexcept
    {
        constexpr static u16 size = 2 * sizeof(float);
        attributes.emplace_back(GL_FLOAT, size, 2, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushVec3(bool normalize) noexcept
    {
        constexpr static u16 size = 3 * sizeof(float);
        attributes.emplace_back(GL_FLOAT, size, 3, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushVec4(bool normalize) noexcept
    {
        constexpr static u16 size = 4 * sizeof(float);
        attributes.emplace_back(GL_FLOAT, size, 4, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushiVec2(bool normalize) noexcept
    {
        constexpr static u16 size = 2 * sizeof(int);
        attributes.emplace_back(GL_INT, size, 2, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushiVec3(bool normalize) noexcept
    {
        constexpr static u16 size = 3 * sizeof(int);
        attributes.emplace_back(GL_INT, size, 3, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushiVec4(bool normalize) noexcept
    {
        constexpr static u16 size = 4 * sizeof(int);
        attributes.emplace_back(GL_INT, size, 4, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushuVec2(bool normalize) noexcept
    {
        constexpr static u16 size = 2 * sizeof(uint);
        attributes.emplace_back(GL_UNSIGNED_INT, size, 2, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushuVec3(bool normalize) noexcept
    {
        constexpr static u16 size = 3 * sizeof(uint);
        attributes.emplace_back(GL_UNSIGNED_INT, size, 3, normalize);
        return *this;
    }
    
    VertexBufferLayout& VertexBufferLayout::pushuVec4(bool normalize) noexcept
    {
        constexpr static u16 size = 4 * sizeof(uint);
        attributes.emplace_back(GL_UNSIGNED_INT, size, 4, normalize);
        return *this;
    }

    void VertexBufferLayout::bind() const noexcept
    {
        size_t stride = 0u;
        size_t offset = 0u;
        for(size_t i = 0; i < attributes.size(); ++i)
        {
            const VertexAttributeLayout& attribute = attributes[i];

            stride += attribute.size;
            glCall(glEnableVertexAttribArray(i));
            glCall(glVertexAttribPointer(i, attribute.componentCount, attribute.glType, attribute.normalized ? GL_TRUE : GL_FALSE, stride, (const void*)offset));
            offset += attribute.size;
        }
    }
}