#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include "typedefs.hpp"

namespace prim
{
    enum class ShaderType { Vertex, Fragment, _length };
    static constexpr const char* ShaderType_s[] = { "Vertex", "Fragment"};

    class Shader
    {
    private:
        ShaderType type;
        glenum glType;
        u32 glId;
    public:
        Shader(ShaderType type, const char* filepath);
        Shader(Shader&& rhs);
        Shader& operator=(Shader&& rhs);
        ~Shader();

        u32 getId() const noexcept;
        ShaderType getType() const noexcept;
        glenum getGlType() const noexcept;
    };
}

#endif // __SHADER_HPP__