#ifndef __SHADER_PIPELINE_HPP__
#define __SHADER_PIPELINE_HPP__

#include <vector>
#include <unordered_map>
#include <string>
#include "glm/glm.hpp"
#include "shader.hpp"

namespace prim
{
    class ShaderPipeline
    {
    private:
        u32 glId;
        ShaderPipelineType pipelineType;
        mutable std::unordered_map<std::string, u32> uniformLocationCache;

        i32 getUniformLocation(const char* name) const;
    public:
        ShaderPipeline(ShaderPipelineType pipelineType, std::initializer_list<const Shader*> shaders);
        ~ShaderPipeline();

        void bind() const noexcept;
        void unbind() const noexcept;

        template<class T>
        void setUniform(const char* name, T value) const;
    };
}

#endif // __SHADER_PIPELINE_HPP__