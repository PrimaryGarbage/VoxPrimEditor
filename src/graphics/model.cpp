#include "model.hpp"

namespace prim
{
    Model::Model(std::vector<ShadedMesh>&& _meshes) : meshes(std::move(_meshes))
    {}
    
    Model::Model(Model&& rhs) : meshes(std::move(rhs.meshes))
    {}
    
    Model& Model::operator=(Model&& rhs)
    {
        meshes = std::move(rhs.meshes);    
        return *this;
    }
    
    const std::vector<ShadedMesh>& Model::getMeshes() const noexcept
    {
        return meshes;
    }
}