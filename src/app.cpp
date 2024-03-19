#include "app.hpp"
#include "external/glad.h"
#include "graphics/renderer.hpp"
#include "input.hpp"
#include "exception.hpp"
#include "graphics/voxel.hpp"
#include "graphics/primitives.hpp"

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

    int App::run()
    {
        renderer->setClearColor(Colors::green);

        Voxel voxel;
        voxel.transform.scale *= 3;
        voxel.albedo = Colors::blue;

        const static float speed = 0.1f;
        Camera* camera = renderer->getCamera();
        camera->transform.position.z = 10.0f;

        while(!renderer->windowShouldClose())
        {
            BEGIN_MAIN_LOOP

            //// Draw here ////
            voxel.draw(*renderer.get());
            ///////////////////

            renderer->endFrame();
            input->reset();
            glfwPollEvents();

            camera->transform.position.x += input->getAxis("Horizontal") * speed;
            camera->transform.position.y += input->getAxis("Vertical") * speed;

            END_MAIN_LOOP
        }

        return 0;
    }
}