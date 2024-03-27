#include "shader_pipeline.hpp"
#include "opengl_utils.hpp"
#include "external/glad.h"
#include "opengl_utils.hpp"
#include "exception.hpp"

namespace prim
{
    ShaderPipeline::ShaderPipeline(ShaderPipelineType pipelineType, std::initializer_list<const Shader*> shaders) : pipelineType(pipelineType)
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
            glCall(glGetProgramInfoLog(glId, infoLogLength, NULL, &errorMessage[0]));
            Logger::inst().logError("Error during shader program linkage. Error message: {0}", errorMessage.c_str());
        }
        else
        {
            Logger::inst().logInfo("Shader program linked successfully. Shader pipeline type: {0}", enum_str(pipelineType));
        }

        for(const Shader* shader : shaders)
        {
            glCall(glDetachShader(glId, shader->getId()));
        }
    }
    
    ShaderPipeline::~ShaderPipeline()
    {
        glCall(glDeleteProgram(glId));
        Logger::inst().logInfo("Shader program deleted. GL ID: {0}, shader pipeline type: {1}", glId, enum_str(pipelineType));
    }

    i32 ShaderPipeline::getUniformLocation(const char* name) const
    {
        const auto& foundIter = uniformLocationCache.find(name);
        if(foundIter == uniformLocationCache.end())
        {
            i32 uniformId;
            glCall(uniformId = glGetUniformLocation(glId, name));
            if(uniformId < 0) throw EXCEPTION(std::format("Failed to find shader uniform with the given name. Name: {0}", name));

            uniformLocationCache[name] = uniformId;
            return uniformId;
        }
        else
        {
            return foundIter->second;
        }
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

#include "shader_pipeline.tpp"