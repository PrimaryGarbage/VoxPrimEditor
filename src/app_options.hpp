#ifndef __APP_OPTIONS_HPP__
#define __APP_OPTIONS_HPP__

#include "input_utils.hpp"

namespace prim
{
    struct AppOptions
    {
        inline static float cameraRotationSpeed{0.1f};
        inline static float cameraMoveSpeed{0.1f};
        inline static float cameraMoveSpeedMultiplier{3.0f};
        inline static Key cameraMoveMultiplierKey{Key::leftShift};
    };
}

#endif // __APP_OPTIONS_HPP__