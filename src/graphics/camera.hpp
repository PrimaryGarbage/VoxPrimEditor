#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "typedefs.hpp"
#include "transform.hpp"

namespace prim
{
    class Camera
    {
    public:
        Transform transform;
        float fovDegrees{70.0f};
        float zNear{0.1f};
        float zFar{100.0f};
        glm::mat4 getProjectionMatrix(glm::vec2 windowSize) const noexcept;
        glm::mat4 getViewMatrix() const noexcept;
    };
}

#endif // __CAMERA_HPP__