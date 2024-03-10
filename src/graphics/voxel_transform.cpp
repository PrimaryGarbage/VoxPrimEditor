#include "voxel_transform.hpp"

namespace prim
{
    glm::mat4 VoxelTransform::getModelMatrix() const noexcept
    {
        return glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(scale)) * glm::toMat4(rotation), position);
    }
}