#include "transform.hpp"
namespace prim
{
    glm::mat4 Transform::getModelMatrix() const noexcept
    {
        return glm::translate((glm::scale(glm::mat4(1.0f), scale)) * glm::toMat4(rotation), position);
    }
    
    glm::vec3 Transform::forward() const noexcept
    {
        return glm::rotate(rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    }
    
    glm::vec3 Transform::backward() const noexcept
    {
        return glm::rotate(rotation, glm::vec3(0.0f, 0.0f, -1.0f));
    }
    
    glm::vec3 Transform::right() const noexcept
    {
        return glm::rotate(rotation, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    
    glm::vec3 Transform::left() const noexcept
    {
        return glm::rotate(rotation, glm::vec3(-1.0f, 0.0f, 0.0f));
    }
    
    glm::vec3 Transform::up() const noexcept
    {
        return glm::rotate(rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
    glm::vec3 Transform::down() const noexcept
    {
        return glm::rotate(rotation, glm::vec3(0.0f, -1.0f, 0.0f));
    }
}