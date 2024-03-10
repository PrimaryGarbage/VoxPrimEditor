#include "camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

namespace prim
{
    glm::mat4 Camera::getProjectionMatrix(glm::vec2 windowSize) const noexcept
    {
        return glm::perspectiveFov(glm::radians(fovDegrees), windowSize.x, windowSize.y, zNear, zFar);
    }

    glm::mat4 Camera::getViewMatrix() const noexcept
    {
        glm::mat4 mat(1.0f);
        glm::quat rotation(transform.rotation.w, -transform.rotation.x, -transform.rotation.y, -transform.rotation.z);
        return glm::toMat4(rotation) * glm::translate(mat, -transform.position);
    }
}
