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
#include "shader_utils.hpp"
#include <unordered_map>

namespace prim
{
    //forward declaration
    class ShaderPipeline;

    enum class CursorMode { 
        Normal = GLFW_CURSOR_NORMAL, 
        Captured = GLFW_CURSOR_CAPTURED, 
        Disabled = GLFW_CURSOR_DISABLED,
        Hidden = GLFW_CURSOR_HIDDEN
    };

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
        std::unordered_map<ShaderPipelineType, Unp<ShaderPipeline>> shaderPipelineCache;

        Logger logger;

        static void errorCallback(int error, const char* description);
        static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height);
        
        void updateVPMatrix();
        ShaderPipeline* loadShaderPipeline(ShaderPipelineType type);
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
        void setCursorMode(CursorMode mode) const noexcept;
        const ShaderPipeline* getShaderPipeline(ShaderPipelineType type);
        Camera* getCamera() noexcept;
    };
}


#endif // __RENDERER_HPP__