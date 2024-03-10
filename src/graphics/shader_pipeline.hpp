#ifndef __SHADER_PIPELINE_HPP__
#define __SHADER_PIPELINE_HPP__

#include <vector>
#include "shader.hpp"

namespace prim
{
    class ShaderPipeline
    {
    private:
        u32 glId;
    public:
        ShaderPipeline(std::initializer_list<const Shader*> shaders);
        ~ShaderPipeline();

        void bind() const noexcept;
        void unbind() const noexcept;
    };
}

#endif // __SHADER_PIPELINE_HPP__