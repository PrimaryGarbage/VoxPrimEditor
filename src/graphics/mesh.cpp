#include "mesh.hpp"

namespace prim
{
    Mesh::Mesh(VertexBuffer&& vb, IndexBuffer&& ib) : vertexBuffer(std::move(vb)), indexBuffer(std::move(ib))
    {}

    Mesh::Mesh(Mesh&& rhs) : vertexBuffer(std::move(rhs.vertexBuffer)), indexBuffer(std::move(rhs.indexBuffer))
    {}
    
    Mesh& Mesh::operator=(Mesh&& rhs)
    {
        vertexBuffer.~VertexBuffer();
        indexBuffer.~IndexBuffer();
        vertexBuffer = std::move(rhs.vertexBuffer);
        indexBuffer = std::move(rhs.indexBuffer);

        return *this;
    }

    void Mesh::bind() const noexcept
    {
        vertexBuffer.bind();
        indexBuffer.bind();
    }

    u32 Mesh::elementCount() const noexcept
    {
        return indexBuffer.getCount();
    }
}