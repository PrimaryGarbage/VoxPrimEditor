#define GLFW_INCLUDE_NONE
#include "external/glad.h"
#include "renderer.hpp"
#include "exception.hpp"
#include "input.hpp"
#include "opengl_utils.hpp"
#include "shader_pipeline.hpp"
#include "primitives.hpp"
#include "shader_pipeline_type.hpp"
#include <functional>
#include <filesystem>

namespace prim
{
    std::unordered_map<const GLFWwindow*, Renderer*> Renderer::rendererMapping;

    Renderer::Renderer(u32 windowWidth, u32 windowHeight, const char* windowTitle) : windowSize(windowWidth, windowHeight)
    {
        try
        {
            if(!glfwInit())
            {
                throw EXCEPTION("Failed to initialize glfw");
            }

            glfwSetErrorCallback(errorCallback);

            // TODO: set glfwWindowHint to restrict allowed OpenGL version
            // 4x antialiasing
            glfwWindowHint(GLFW_SAMPLES, 4);
            // we need opengl 3.3
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            // for macos compatibility?
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = glfwCreateWindow(640, 480, "WindowTitle", nullptr, nullptr);
            if(!window) throw EXCEPTION("Failed to create GLFW window.");

            glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

            glfwMakeContextCurrent(window);

            glfwSwapInterval(1);

            int gladReturnValue = gladLoadGL();
            if(!gladReturnValue) throw EXCEPTION("Failed to initialize GLAD");

            glCall(glEnable(GL_CULL_FACE));

            glCall(glGenVertexArrays(1, &vertexArrayId));
            glCall(glBindVertexArray(vertexArrayId));

            shaderPipelineCache[ShaderPipelineType::Default] = Unp<ShaderPipeline>(loadShaderPipeline(ShaderPipelineType::Default));
            currentShader = shaderPipelineCache[ShaderPipelineType::Default].get();
            currentShader->bind();

            // setup default primitives for common use. Maybe there's a better way to handle this
            defaultPrimitives = std::make_unique<DefaultPrimitives>();
            defaultPrimitives->cube.reset(new Mesh(Primitives::cube(1.0f)));
            defaultPrimitives->plane.reset(new Mesh(Primitives::plane(1.0f, 1.0f)));

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
        // delete managed openGL resources before calling to glfwTerminate()
        for(auto& shaderPair : shaderPipelineCache)
        {
            shaderPair.second.reset();
        }
        defaultPrimitives.reset();

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
    
    const ShaderPipeline* Renderer::getCurrentShader() const noexcept
    {
        return currentShader;
    }
    
    void Renderer::endFrame()
    {
        glfwSwapBuffers(window);
        glCall(glViewport(0, 0, windowSize.x, windowSize.y));
        glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        isVPMatrixStale = true;
    }

    void Renderer::setClearColor(Color color) noexcept
    {
        glm::vec4 colorVec(color);
        glCall(glClearColor(colorVec.r, colorVec.g, colorVec.b, colorVec.a));
    }

    void Renderer::draw(const Mesh& mesh)
    {
        if(!currentShader) setCurrentShaderPipeline(shaderPipelineCache[ShaderPipelineType::Default].get());

        mesh.bind();
        glCall(glDrawElements(GL_TRIANGLES, mesh.elementCount(), GL_UNSIGNED_INT, NULL));
    }
    
    void Renderer::draw(const ShadedMesh& mesh)
    {
        mesh.bind();
        glCall(glDrawElements(GL_TRIANGLES, mesh.elementCount(), GL_UNSIGNED_INT, NULL));
        setCurrentShaderPipeline(currentShader);
    }
    
    void Renderer::draw(const Model& model)
    {
        for(const ShadedMesh& mesh : model.getMeshes())
        {
            mesh.bind();
            glCall(glDrawElements(GL_TRIANGLES, mesh.elementCount(), GL_UNSIGNED_INT, NULL));
        }
        setCurrentShaderPipeline(currentShader);
    }
    
    void Renderer::setCurrentShaderPipeline(const ShaderPipeline* shader) noexcept
    {
        if(currentShader == shader) return;

        currentShader = shader;
        currentShader->bind();
    }
    
    void Renderer::setModelMatrix(glm::mat4 matrix)
    {
        if(isVPMatrixStale) updateVPMatrix();
        currentShader->setUniform("mvp", viewProjectMatrix * matrix);
    }
    
    ShaderPipeline* Renderer::getShaderPipeline(ShaderPipelineType tag)
    {
        if(!shaderPipelineCache.contains(tag))
        {
            shaderPipelineCache[tag] = Unp<ShaderPipeline>(loadShaderPipeline(tag));
        }

        return shaderPipelineCache[tag].get();
    }
    
    Camera* Renderer::getCamera() noexcept
    {
        return &camera;
    }
    
    const DefaultPrimitives* Renderer::getDefaultPrimitives() const noexcept
    {
        return defaultPrimitives.get();
    }

    // glfw callbacks //
    void Renderer::errorCallback(int error, const char* description)
    {
        Logger::inst().logError("GLFW error. ErrorNo: {0}; Description: {1}", error, description);
    }
    
    void Renderer::framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height)
    {
        rendererMapping[window]->windowSize = glm::uvec2(width, height);
    }
    
    void Renderer::updateVPMatrix()
    {
        viewProjectMatrix = camera.getProjectionMatrix(windowSize) * camera.getViewMatrix();
        isVPMatrixStale = false;
    }
    
    ShaderPipeline* Renderer::loadShaderPipeline(ShaderPipelineType shaderTag)
    {
        using Path = std::filesystem::path;

        static const char* shaderDirPath = "res/shaders";

        Path fullVertexShaderPath = Path(shaderDirPath) / (std::string(shaderFilepaths[static_cast<int>(shaderTag)]) + vertPostfix + shaderExtension);
        Path fullFragmentShaderPath = Path(shaderDirPath) / (std::string(shaderFilepaths[static_cast<int>(shaderTag)]) + fragPostfix + shaderExtension);

        Shader vertexShader(ShaderType::Vertex, fullVertexShaderPath.string().c_str());
        Shader fragmentShader(ShaderType::Fragment, fullFragmentShaderPath.string().c_str());

        return new ShaderPipeline({&vertexShader, &fragmentShader});
    }
}