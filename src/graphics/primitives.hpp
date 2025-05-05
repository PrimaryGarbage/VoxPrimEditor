#ifndef __PRIMITIVES_HPP__
#define __PRIMITIVES_HPP__

#include "mesh.hpp"
#include "typedefs.hpp"

namespace prim
{
    class Primitives
    {
    public:
        static const Mesh* defaultCube();
        static const Mesh* defaultPlane();

        static Mesh createCubeMesh(float size);
        static Mesh createPlaneMesh(float width, float heigth);
    };
}

#endif // __PRIMITIVES_HPP__