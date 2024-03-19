#include "voxel.hpp"
#include "renderer.hpp"
#include "primitives.hpp"
#include "shader_pipeline.hpp"

namespace prim
{
    void Voxel::draw(Renderer& renderer) const
    {
        renderer.setModelMatrix(transform.getModelMatrix());
        renderer.getCurrentShader()->setUniform("albedo", albedo);
        renderer.draw(*renderer.getDefaultPrimitives()->cube);
    }
}