#ifndef __VOXEL_HPP__
#define __VOXEL_HPP__

#define GLM_ENABLE_EXPERIMENTAL

#include "voxel_transform.hpp"
#include "color.hpp"

namespace prim
{
    class Renderer;

    class Voxel
    {
    public:
        VoxelTransform transform;
        Color albedo;
        void draw(Renderer& renderer) const noexcept;
    };
}

#endif // __VOXEL_HPP__