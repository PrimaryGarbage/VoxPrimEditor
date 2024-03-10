#include "app.hpp"
#include "external/glad.h"
#include "graphics/renderer.hpp"
#include "input.hpp"
#include "exception.hpp"
#include "graphics/primitives.hpp"
#include "graphics/shader_pipeline.hpp"
#include "graphics/shader.hpp"

#define BEGIN_MAIN_LOOP try{
#define END_MAIN_LOOP }catch(Exception ex){logger.logError(ex.what());}

// initial window parameters
static constexpr u32 initialWindowWidth = 640u;
static constexpr u32 initialWindowHeight = 480u;
static const char* windowTitle = "VoxPrim editor";

namespace prim
{
    App::App() : renderer(new Renderer(initialWindowWidth, initialWindowHeight, windowTitle)), input(new Input(renderer->getWindow()))
    {}
    
    App::~App()
    {}

    int App::run() noexcept
    {
        renderer->setClearColor(Colors::black);

        Mesh cubeMesh = Primitives::cube(1.0f);

        while(!renderer->windowShouldClose())
        {
            BEGIN_MAIN_LOOP

            //// Draw here ////
            renderer->draw(cubeMesh);
            ///////////////////

            renderer->endFrame();
            input->reset();
            glfwPollEvents();

            END_MAIN_LOOP
        }

        return 0;
    }
}