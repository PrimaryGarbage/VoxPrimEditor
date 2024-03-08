#define GLFW_INCLUDE_NONE
#include "external/glad.h"
#include "GLFW/glfw3.h"
#include "renderer.hpp"
#include "exception.hpp"
#include "input.hpp"
#include <functional>

namespace prim
{
    std::unordered_map<const GLFWwindow*, Renderer*> Renderer::rendererMapping;

    Renderer::Renderer()
    {
        try
        {
            if(!glfwInit())
            {
                throw EXCEPTION("Failed to initialize glfw");
            }

            glfwSetErrorCallback(errorCallback);

            // TODO: set glfwWindowHint to restrict allowed OpenGL version

            glfwSwapInterval(1);

            window = glfwCreateWindow(640, 480, "WindowTitle", nullptr, nullptr);
            if(!window) throw EXCEPTION("Failed to create GLFW window.");


            glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

            glfwMakeContextCurrent(window);
            int gladReturnValue = gladLoadGL();
            if(!gladReturnValue) throw EXCEPTION("Failed to initialize GLAD");

            rendererMapping[window] = this;
        }
        catch(Exception ex)
        {
            rendererMapping.erase(window);
            glfwTerminate();
            throw ex;
        }
    }

    Renderer::~Renderer()
    {
        glfwDestroyWindow(window);
        rendererMapping.erase(window);
        window = nullptr;
        logger.logInfo("GLFW window destroyed successfully.");
        glfwTerminate();
        logger.logInfo("GLFW terminated successfully.");
    }

    bool Renderer::windowShouldClose() const noexcept
    {
        return glfwWindowShouldClose(window);
    }
    
    GLFWwindow* Renderer::getWindow() const noexcept
    {
        return window;
    }

    glm::uvec2 Renderer::getWindowSize() const noexcept
    {
        return windowSize;
    }
    
    void Renderer::drawFrame()
    {
        glad_glViewport(0, 0, windowSize.x, windowSize.y);
        glad_glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    void Renderer::setClearColor(Color color) noexcept
    {
        glm::vec4 colorVec(color);
        glad_glClearColor(colorVec.r, colorVec.g, colorVec.b, colorVec.a);
    }

    // glfw callbacks //
    void Renderer::errorCallback(int error, const char* description)
    {
        logger.logError("GLFW error. ErrorNo: {0}; Description: {1}", error, description);
    }
    
    void Renderer::framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height)
    {
        rendererMapping[window]->windowSize = glm::uvec2(width, height);
    }
}