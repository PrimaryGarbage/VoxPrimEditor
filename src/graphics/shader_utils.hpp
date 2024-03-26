#ifndef __SHADER_TAG_HPP__
#define __SHADER_TAG_HPP__

#include <string>
#include "enum_utils.hpp"
#include "string_tools.hpp"

namespace prim
{
    enum class ShaderType 
    { 
        Vertex, 
        Fragment 
    };

    enum class ShaderPipelineType
    {
        Default,
        Voxel
    };

    inline std::string getShaderFileName(ShaderPipelineType pipelineType, ShaderType shaderType)
    {
        return toLower(std::string(enum_str(pipelineType))) + '_' + toLower(std::string(enum_str(shaderType)));
    }
}

#endif // __SHADER_TAG_HPP__