#include "primitives.hpp"
#include "typedefs.hpp"

namespace prim
{
    Mesh Primitives::cube(float size)
    {
        constexpr static u32 dataSize = 24 * sizeof(float);
        constexpr static u32 indexCount = 36;

        constexpr static u32 indexData[] = {
            0, 1, 3,
            1, 2, 3,
            3, 2, 7,
            2, 6, 7,
            4, 5, 7,
            5, 6, 7,
            0, 1, 4,
            1, 5, 7,
            1, 5, 2,
            5, 6, 2,
            0, 4, 3,
            4, 7, 3
        };

        float half = size / 2.0f;

        float positionData[] = {
            -half, -half, -half,
            half, -half, -half,
            half, half, -half,
            -half, half, -half,
            -half, -half, half,
            half, -half, half,
            half, half, half,
            -half, half, half
        };

        VertexBufferLayout layout;
        layout.pushVec3();

        return Mesh(VertexBuffer(positionData, dataSize, layout), IndexBuffer(indexData, indexCount));
    }
    
    Mesh Primitives::plane(float width, float heigth)
    {
        constexpr static u32 dataSize = 12 * sizeof(float);
        constexpr static u32 indexCount = 6;

        constexpr static u32 indexData[] = {
            0, 1, 3,
            1, 2, 3,
        };

        float halfW = width / 2.0f;
        float halfH = heigth / 2.0f;

        float positionData[] = {
            -halfW, -halfH, -1.0f,
            halfW, -halfH, -1.0f,
            halfW, halfH, -1.0f,
            -halfW, halfH, -1.0f,
        };

        VertexBufferLayout layout;
        layout.pushVec3();

        return Mesh(VertexBuffer(positionData, dataSize, layout), IndexBuffer(indexData, indexCount));
    }
}