#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

namespace prim
{
    struct Transform
    {
        glm::vec3 position{0.0f, 0.0f, 0.0f};
        glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};
        glm::vec3 scale{1.0f, 1.0f, 1.0f};

        glm::mat4 getModelMatrix() const noexcept;
    };
}

#endif // __TRANSFORM_HPP__