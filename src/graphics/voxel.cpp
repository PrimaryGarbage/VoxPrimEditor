#include "voxel.hpp"
#include "renderer.hpp"
#include "primitives.hpp"
#include "shader_pipeline.hpp"
#include "shader_utils.hpp"

namespace prim
{
    void Voxel::draw(Renderer& renderer) const
    {
        static const ShaderPipeline* shader = renderer.getShaderPipeline(ShaderPipelineType::Voxel);
        static const Mesh* cubeMesh = Primitives::defaultCube();
        shader->setUniform("albedo", albedo);
        renderer.setModelMatrix(transform.getModelMatrix());
        renderer.setCurrentShaderPipeline(shader);
        renderer.draw(*cubeMesh);
    }
}