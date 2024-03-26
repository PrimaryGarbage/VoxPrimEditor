#include "voxel.hpp"
#include "renderer.hpp"
#include "primitives.hpp"
#include "shader_pipeline.hpp"
#include "shader_utils.hpp"

namespace prim
{
    void Voxel::draw(Renderer& renderer) const
    {
        ShaderPipeline* shader = renderer.getShaderPipeline(ShaderPipelineType::Voxel);
        shader->setUniform("albedo", albedo);
        renderer.setModelMatrix(transform.getModelMatrix());
        renderer.setCurrentShaderPipeline(shader);
        renderer.draw(*renderer.getDefaultPrimitives()->cube);
    }
}