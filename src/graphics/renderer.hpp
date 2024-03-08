#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "logger.hpp"
#include "typedefs.hpp"
#include "glm/glm.hpp"
#include "color.hpp"
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

        inline static Logger logger;

        static void errorCallback(int error, const char* description);
        static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height);
    public:
        Renderer();
        ~Renderer();

        bool windowShouldClose() const noexcept;
        GLFWwindow* getWindow() const noexcept;
        glm::uvec2 getWindowSize() const noexcept;
        void drawFrame();
        void setClearColor(Color color) noexcept;
    };
}


#endif // __RENDERER_HPP__