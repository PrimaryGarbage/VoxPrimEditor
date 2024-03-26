#include "shader.hpp"
#include "external/glad.h"
#include "opengl_utils.hpp"
#include <fstream>
#include <sstream>
#include "exception.hpp"

namespace prim
{
    static glenum getGlShaderType(ShaderType type)
    {
        switch(type)
        {
            case ShaderType::Vertex:
                return GL_VERTEX_SHADER;
            case ShaderType::Fragment:
                return GL_FRAGMENT_SHADER;
            default:
                throw EXCEPTION("Invalid shader type");
        }
    }

    Shader::Shader(ShaderPipelineType pipelineType, ShaderType type, std::string data) 
        : pipelineType(pipelineType), type(type), glType(getGlShaderType(type))
    {
        glCall(glId = glCreateShader(getGlShaderType(type)));

        const char* const srcPtr = data.c_str();
        glCall(glShaderSource(glId, 1, &srcPtr, NULL));
        glCall(glCompileShader(glId));

        i32 compilationResult = GL_FALSE;
        i32 infoLogLength;
        glCall(glGetShaderiv(glId, GL_COMPILE_STATUS, &compilationResult));
        glCall(glGetShaderiv(glId, GL_INFO_LOG_LENGTH, &infoLogLength));
        if(infoLogLength > 0)
        {
            std::string shaderErrorMessage;
            shaderErrorMessage.reserve(infoLogLength + 1);
            glCall(glGetShaderInfoLog(glId, infoLogLength, NULL, &shaderErrorMessage[0]));
            Logger::inst().logError("Error during shader compilation. Shader pipeline type: {0}; Error message: {1}", enum_str(pipelineType), shaderErrorMessage);
        }
        else
        {
            Logger::inst().logInfo("Finished shader compilation. Shader pipeline type: {0}", enum_str(pipelineType));
        }
    }
    
    Shader::Shader(Shader&& rhs) : glId(rhs.glId), type(rhs.type), glType(rhs.glType)
    {
        rhs.glId = 0;
    }
    
    Shader& Shader::operator=(Shader&& rhs)
    {
        this->~Shader();
        glId = rhs.glId;
        type = rhs.type;
        glType = rhs.glType;

        rhs.glId = 0;

        return *this;
    }
    
    Shader::~Shader()
    {
        if(glId != 0) 
        {
            glCall(glDeleteShader(glId));
            glId = 0;
            Logger::inst().logInfo("Shader deleted. Shader pipeline type: {0}, Shader type: {1}", enum_str(pipelineType), enum_str(type));
        }
    }
    
    u32 Shader::getId() const noexcept
    {
        return glId;
    }
    
    ShaderType Shader::getType() const noexcept
    {
        return type;
    }
    
    glenum Shader::getGlType() const noexcept
    {
        return glType;
    }
}