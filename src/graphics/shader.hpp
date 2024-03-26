#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include "typedefs.hpp"
#include "shader_utils.hpp"

namespace prim
{

    class Shader
    {
    private:
        ShaderType type;
        ShaderPipelineType pipelineType;
        glenum glType;
        u32 glId;
    public:
        Shader(ShaderPipelineType pipelineType, ShaderType type, std::string data);
        Shader(Shader&& rhs);
        Shader& operator=(Shader&& rhs);
        ~Shader();

        u32 getId() const noexcept;
        ShaderType getType() const noexcept;
        glenum getGlType() const noexcept;
    };
}

#endif // __SHADER_HPP__