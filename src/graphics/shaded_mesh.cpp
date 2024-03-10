#include "shaded_mesh.hpp"
#include "shader_pipeline.hpp"

namespace prim
{
    ShadedMesh::ShadedMesh(Mesh&& mesh, ShaderPipeline* shader) : mesh(std::move(mesh)), shader(shader)
    {}
    
    ShadedMesh::ShadedMesh(ShadedMesh&& rhs) : mesh(std::move(rhs.mesh)), shader(rhs.shader)
    {}
    
    ShadedMesh& ShadedMesh::operator=(ShadedMesh&& rhs)
    {
        mesh = std::move(rhs.mesh);
        shader = rhs.shader;

        return *this;
    }
    
    void ShadedMesh::bind() const noexcept
    {
        mesh.bind();
        shader->bind();
    }
    u32 ShadedMesh::elementCount() const noexcept
    {
        return mesh.elementCount();
    }
}