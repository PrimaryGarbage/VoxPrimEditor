#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <vector>
#include "shaded_mesh.hpp"

namespace prim
{
    class Model
    {
    private:
        std::vector<ShadedMesh> meshes;
    public:
        Model(std::vector<ShadedMesh>&& meshes);
        Model(Model&& rhs);
        Model& operator=(Model&& rhs);

        const std::vector<ShadedMesh>& getMeshes() const noexcept;
    };
}

#endif // __MODEL_HPP__