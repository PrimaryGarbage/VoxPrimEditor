#ifndef __SHADER_TAG_HPP__
#define __SHADER_TAG_HPP__

namespace prim
{
    inline const char* vertPostfix = "_vertex";
    inline const char* fragPostfix = "_fragment";
    inline const char* shaderExtension = ".glsl";

    enum class ShaderPipelineType
    {
        Default,
        Voxel,
        _length
    };

    inline const char* ShaderPipelineType_str[] = {
        "Default",
        "Voxel"
    };

    inline const char* shaderFilepaths[] = {
        "default",
        "voxel",
    };
}

#endif // __SHADER_TAG_HPP__