#include "transform.hpp"
namespace prim
{
    glm::mat4 Transform::getModelMatrix() const noexcept
    {
        return glm::translate((glm::scale(glm::mat4(1.0f), scale)) * glm::toMat4(rotation), position);
    }
}