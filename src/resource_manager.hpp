#ifndef __RESOURCE_MANAGER_HPP__
#define __RESOURCE_MANAGER_HPP__

#include <string>
#include <filesystem>
#include <optional>

namespace prim
{
    class ResourceManager
    {
    private:
        static const std::filesystem::path resDirPath;
        static const std::filesystem::path shaderDirPath;
        static const char* shaderFileExtension;

        static std::optional<std::filesystem::path> findFileRecursively(std::filesystem::path dirPath, std::string filename);
    public:
        static std::string loadShader(std::string shaderName);
    };
}

#endif // __RESOURCE_MANAGER_HPP__