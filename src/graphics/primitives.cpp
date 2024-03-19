#include "primitives.hpp"
#include "typedefs.hpp"

namespace prim
{
    Mesh Primitives::cube(float size)
    {
        constexpr static u32 dataSize = 48 * sizeof(float);
        constexpr static u32 indexCount = 36;

        constexpr static u32 indexData[] = {
            0, 1, 3,
            1, 2, 3,
            3, 7, 2,
            2, 7, 6,
            4, 5, 7,
            5, 6, 7,
            0, 1, 4,
            1, 5, 4,
            1, 2, 5,
            5, 2, 6,
            0, 4, 3,
            4, 7, 3
        };

        float half = size / 2.0f;

        float vertexData[] = {
            -half, -half, -half, 0.0f, 0.0f, 0.0f,
            half, -half, -half, 1.0f, 0.0f, 0.0f,
            half, half, -half, 1.0f, 1.0f, 0.0f,
            -half, half, -half, 0.0f, 1.0f, 0.0f,
            -half, -half, half, 0.0f, 0.0f, 1.0f,
            half, -half, half, 1.0f, 0.0f, 1.0f,
            half, half, half, 1.0f, 1.0f, 1.0f,
            -half, half, half, 0.0f, 1.0f, 1.0f
        };

        VertexBufferLayout layout;
        layout.pushVec3().pushVec3();

        return Mesh(VertexBuffer(vertexData, dataSize, layout), IndexBuffer(indexData, indexCount));
    }
    
    Mesh Primitives::plane(float width, float heigth)
    {
        constexpr static u32 dataSize = 20 * sizeof(float);
        constexpr static u32 indexCount = 6;

        constexpr static u32 indexData[] = {
            0, 1, 3,
            1, 2, 3,
        };

        float halfW = width / 2.0f;
        float halfH = heigth / 2.0f;

        float vertexData[] = {
            -halfW, -halfH, 0.0f, 0.0f, 0.0f,
            halfW, -halfH, 0.0f, 1.0f, 0.0f,
            halfW, halfH, 0.0f, 1.0f, 1.0f,
            -halfW, halfH, 0.0f, 0.0f, 1.0f
        };

        VertexBufferLayout layout;
        layout.pushVec3().pushVec2();

        return Mesh(VertexBuffer(vertexData, dataSize, layout), IndexBuffer(indexData, indexCount));
    }
}