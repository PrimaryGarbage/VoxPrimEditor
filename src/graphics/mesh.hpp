#ifndef __MESH_HPP__
#define __MESH_HPP__

#include "vertex_buffer.hpp"
#include "index_buffer.hpp"

namespace prim
{
    class Mesh
    {
    private:
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        
    public:
        Mesh(VertexBuffer&& vb, IndexBuffer&& ib);
        Mesh(Mesh&& rhs);
        Mesh& operator=(Mesh&& rhs);

        void bind() const noexcept;
        u32 elementCount() const noexcept;
    };
}

#endif // __MESH_HPP__