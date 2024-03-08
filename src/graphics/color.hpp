#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include "glm/glm.hpp"


namespace prim
{
    typedef glm::vec4 Color;

    struct Colors final
    {
        constexpr static Color red{1.0f, 0.0f, 0.0f, 1.0f};
        constexpr static Color green{0.0f, 1.0f, 0.0f, 1.0f};
        constexpr static Color blue{0.0f, 0.0f, 1.0f, 1.0f};
        constexpr static Color black{0.0f, 0.0f, 0.0f, 1.0f};
        constexpr static Color white{1.0f, 1.0f, 1.0f, 1.0f};
        constexpr static Color transparent{1.0f, 1.0f, 1.0f, 0.0f};
    };
}

#endif // __COLOR_HPP__