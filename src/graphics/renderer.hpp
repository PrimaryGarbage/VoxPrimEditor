#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "logger.hpp"
#include "typedefs.hpp"
#include "glm/glm.hpp"
#include "color.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "voxel.hpp"
#include "GLFW/glfw3.h"
#include <unordered_map>

namespace prim
{
    class DefaultPrimitives;
    class ShaderPipeline;
    enum class ShaderPipelineType;

    class Renderer
    {
    private:
        static std::unordered_map<const GLFWwindow*, Renderer*> rendererMapping;

        GLFWwindow* window;
        glm::uvec2 windowSize;
        const ShaderPipeline* currentShader;
        Camera camera;
        u32 vertexArrayId;
        glm::mat4 viewProjectMatrix;
        bool isVPMatrixStale{true};
        Unp<DefaultPrimitives> defaultPrimitives;
        std::unordered_map<ShaderPipelineType, Unp<ShaderPipeline>> shaderPipelineCache;

        Logger logger;

        static void errorCallback(int error, const char* description);
        static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height);
        
        void updateVPMatrix();
        ShaderPipeline* loadShaderPipeline(ShaderPipelineType shaderTag);
    public:
        Renderer(u32 windowWidth, u32 windowHeight, const char* windowTitle);
        ~Renderer();

        bool windowShouldClose() const noexcept;
        GLFWwindow* getWindow() const noexcept;
        glm::uvec2 getWindowSize() const noexcept;
        const ShaderPipeline* getCurrentShader() const noexcept;
        void endFrame();
        void setClearColor(Color color) noexcept;
        void draw(const Mesh& mesh);
        void draw(const ShadedMesh& mesh);
        void draw(const Model& model);
        void setCurrentShaderPipeline(const ShaderPipeline* shader) noexcept;
        void setModelMatrix(glm::mat4 matrix);
        ShaderPipeline* getShaderPipeline(ShaderPipelineType tag);
        Camera* getCamera() noexcept;
        const DefaultPrimitives* getDefaultPrimitives() const noexcept;
    };
}


#endif // __RENDERER_HPP__