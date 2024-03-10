#include "shader_pipeline.hpp"
#include "opengl_utils.hpp"
#include "external/glad.h"

namespace prim
{
    ShaderPipeline::ShaderPipeline(std::initializer_list<const Shader*> shaders)
    {
        glCall(glId = glCreateProgram());
        for(const Shader* shader : shaders)
        {
            glCall(glAttachShader(glId, shader->getId()));
        }
        glCall(glLinkProgram(glId));

        i32 linkResult;
        i32 infoLogLength;
        glCall(glGetProgramiv(glId, GL_LINK_STATUS, &linkResult));
        glCall(glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &infoLogLength));
        if(infoLogLength > 0)
        {
            std::string errorMessage;
            errorMessage.reserve(infoLogLength + 1);
            Logger::inst().logError("Error during shader program linkage. Error message: {0}", errorMessage);
        }
        else
        {
            Logger::inst().logInfo("Shader program linked successfully.");
        }

        for(const Shader* shader : shaders)
        {
            glCall(glDetachShader(glId, shader->getId()));
        }
    }
    
    ShaderPipeline::~ShaderPipeline()
    {
        glCall(glDeleteProgram(glId));
    }
    
    void ShaderPipeline::bind() const noexcept
    {
        glUseProgram(glId);
    }
    
    void ShaderPipeline::unbind() const noexcept
    {
        glUseProgram(0);
    }
}