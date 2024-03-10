#ifndef __SHADED_MESH_HPP__
#define __SHADED_MESH_HPP__

#include "mesh.hpp"

namespace prim
{
    class ShaderPipeline;

    class ShadedMesh
    {
    private:
        Mesh mesh;
        ShaderPipeline* shader;

    public:
        ShadedMesh(Mesh&& mesh, ShaderPipeline* shader);
        ShadedMesh(ShadedMesh&& rhs);
        ShadedMesh& operator=(ShadedMesh&& rhs);

        void bind() const noexcept;
        u32 elementCount() const noexcept;
    };
}

#endif // __SHADED_MESH_HPP__