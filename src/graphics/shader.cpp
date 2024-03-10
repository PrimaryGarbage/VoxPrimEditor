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

    Shader::Shader(ShaderType type, const char* filepath) : type(type), glType(getGlShaderType(type))
    {
        glCall(glId = glCreateShader(getGlShaderType(type)));
        std::ifstream shaderStream(filepath, std::ios::in);
        if(shaderStream.bad()) throw EXCEPTION("Failed to open filestream for shader file.");

        std::stringstream shaderSS;
        shaderSS << shaderStream.rdbuf();
        shaderStream.close();

        std::string src = shaderSS.str();
        const char* const srcPtr = src.c_str();
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
            Logger::inst().logError("Error during shader compilation. Filepath: {0}; Error message: {1}", filepath, shaderErrorMessage.c_str());
        }
        else
        {
            Logger::inst().logInfo("Finished shader compilation. Filepath: {0};", filepath);
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
            Logger::inst().logInfo("Shader deleted.");
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