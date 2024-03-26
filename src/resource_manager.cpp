#include "resource_manager.hpp"
#include "exception.hpp"
#include <fstream>
#include <format>
#include <vector>
#include <sstream>

namespace fs = std::filesystem;

namespace prim
{
    const fs::path ResourceManager::resDirPath = fs::path("res");
    const fs::path ResourceManager::shaderDirPath = fs::path("shaders");
    const char* ResourceManager::shaderFileExtension = ".glsl";

    std::optional<std::filesystem::path> ResourceManager::findFileRecursively(std::filesystem::path dirPath, std::string filename)
    {
        std::vector<fs::path> nestedDirectories;
        for(const auto& entry : fs::directory_iterator(dirPath))
        {
            if(entry.is_directory())
            {
                nestedDirectories.push_back(entry.path());
            }
            else if(entry.is_regular_file())
            {
                fs::path entryPath = entry.path();
                if(entryPath.stem() == filename || entryPath.filename() == filename)
                    return entryPath;
            }
        }

        for(const fs::path& nestedDirPath : nestedDirectories)
        {
            std::optional foundPath = findFileRecursively(nestedDirPath, filename);
            if(foundPath.has_value()) return foundPath.value();
        }

        return std::optional<std::filesystem::path>();
    }

    std::string ResourceManager::loadShader(std::string shaderName)
    {
        const static fs::path shaderDirFullPath = resDirPath / shaderDirPath;
    
        if(shaderName.find('.') == std::string::npos)
            shaderName += shaderFileExtension;

        std::optional filePath = findFileRecursively(shaderDirFullPath, shaderName);

        if(!filePath.has_value()) throw EXCEPTION(std::format("Failed to find shader. Shader name: {0}", shaderName));

        std::ifstream file(filePath.value());
        if(file.bad()) throw EXCEPTION(std::format("Failed to load shader file. Shader name : {0}", shaderName));

        std::stringstream ss;
        ss << file.rdbuf();

        return ss.str();
    }
}