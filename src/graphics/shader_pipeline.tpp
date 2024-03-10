#include "shader_pipeline.hpp"
#include "external/glad.h"
#include "opengl_utils.hpp"
#include "exception.hpp"

namespace prim
{
    template<class T>
    void ShaderPipeline::setUniform(const char* name, T value) const
    {
        throw EXCEPTION("Trying to set shader uniform of unknown type.");
    }

    template<>
    void ShaderPipeline::setUniform<float>(const char* name, float value) const
    {
        glCall(glUniform1f(getUniformLocation(name), value));
    }

    template<>
    void ShaderPipeline::setUniform<i32>(const char* name, i32 value) const
    {
        glCall(glUniform1i(getUniformLocation(name), value));
    }

    template<>
    void ShaderPipeline::setUniform<u32>(const char* name, u32 value) const
    {
        glCall(glUniform1ui(getUniformLocation(name), value));
    }

    template<>
    void ShaderPipeline::setUniform<glm::vec2>(const char* name, glm::vec2 value) const
    {
        glCall(glUniform2f(getUniformLocation(name), value.x, value.y));
    }

    template<>
    void ShaderPipeline::setUniform<glm::ivec2>(const char* name, glm::ivec2 value) const
    {
        glCall(glUniform2i(getUniformLocation(name), value.x, value.y));
    }

    template<>
    void ShaderPipeline::setUniform<glm::uvec2>(const char* name, glm::uvec2 value) const
    {
        glCall(glUniform2ui(getUniformLocation(name), value.x, value.y));
    }

    template<>
    void ShaderPipeline::setUniform<glm::vec3>(const char* name, glm::vec3 value) const
    {
        glCall(glUniform3f(getUniformLocation(name), value.x, value.y, value.z));
    }

    template<>
    void ShaderPipeline::setUniform<glm::ivec3>(const char* name, glm::ivec3 value) const
    {
        glCall(glUniform3i(getUniformLocation(name), value.x, value.y, value.z));
    }

    template<>
    void ShaderPipeline::setUniform<glm::uvec3>(const char* name, glm::uvec3 value) const
    {
        glCall(glUniform3ui(getUniformLocation(name), value.x, value.y, value.z));
    }

    template<>
    void ShaderPipeline::setUniform<glm::vec4>(const char* name, glm::vec4 value) const
    {
        glCall(glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.a));
    }

    template<>
    void ShaderPipeline::setUniform<glm::ivec4>(const char* name, glm::ivec4 value) const
    {
        glCall(glUniform4i(getUniformLocation(name), value.x, value.y, value.z, value.a));
    }

    template<>
    void ShaderPipeline::setUniform<glm::uvec4>(const char* name, glm::uvec4 value) const
    {
        glCall(glUniform4ui(getUniformLocation(name), value.x, value.y, value.z, value.a));
    }

    template<>
    void ShaderPipeline::setUniform<glm::mat4>(const char* name, glm::mat4 value) const
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
    }
}