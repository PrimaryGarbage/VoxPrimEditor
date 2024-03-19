#include "shaded_mesh.hpp"
#include "shader_pipeline.hpp"

namespace prim
{
    ShadedMesh::ShadedMesh(Mesh&& mesh, ShaderPipeline* shaderPipeline) : mesh(std::move(mesh)), shaderPipeline(shaderPipeline)
    {}
    
    ShadedMesh::ShadedMesh(ShadedMesh&& rhs) : mesh(std::move(rhs.mesh)), shaderPipeline(rhs.shaderPipeline)
    {}
    
    ShadedMesh& ShadedMesh::operator=(ShadedMesh&& rhs)
    {
        mesh = std::move(rhs.mesh);
        shaderPipeline = rhs.shaderPipeline;

        return *this;
    }
    
    void ShadedMesh::bind() const noexcept
    {
        mesh.bind();
        shaderPipeline->bind();
    }
    u32 ShadedMesh::elementCount() const noexcept
    {
        return mesh.elementCount();
    }
}