#ifndef __PRIMITIVES_HPP__
#define __PRIMITIVES_HPP__

#include "mesh.hpp"

namespace prim
{
    class DefaultPrimitives
    {
    public:
        Unp<Mesh> cube;
        Unp<Mesh> plane;
    };

    class Primitives
    {
    public:
        static Mesh cube(float size);
        static Mesh plane(float width, float heigth);
    };
}

#endif // __PRIMITIVES_HPP__