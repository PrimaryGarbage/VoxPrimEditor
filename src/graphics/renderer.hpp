#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "logger.hpp"
#include "typedefs.hpp"
#include "glm/glm.hpp"
#include "color.hpp"
#include "model.hpp"
#include <unordered_map>

// forward declaration
class GLFWwindow;

namespace prim
{
    class Renderer
    {
    private:
        static std::unordered_map<const GLFWwindow*, Renderer*> rendererMapping;

        GLFWwindow* window;
        glm::uvec2 windowSize;
        Unp<ShaderPipeline> defaultShader;
        const ShaderPipeline* currentShader;
        u32 vertexArrayId;

        Logger logger;

        static void errorCallback(int error, const char* description);
        static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height);
    public:
        Renderer(u32 windowWidth, u32 windowHeight, const char* windowTitle);
        ~Renderer();

        bool windowShouldClose() const noexcept;
        GLFWwindow* getWindow() const noexcept;
        glm::uvec2 getWindowSize() const noexcept;
        void endFrame();
        void setClearColor(Color color) noexcept;
        void draw(const Mesh& mesh);
        void draw(const ShadedMesh& mesh);
        void draw(const Model& model);
        void setShader(const ShaderPipeline* shader);
    };
}


#endif // __RENDERER_HPP__