#include "app.hpp"
#include "graphics/renderer.hpp"
#include "input.hpp"
#include "exception.hpp"

#define BEGIN_MAIN_LOOP try{
#define END_MAIN_LOOP }catch(Exception ex){logger.logError(ex.what());}

namespace prim
{
    App::App() : renderer(new Renderer()), input(new Input(renderer->getWindow()))
    {}
    
    App::~App()
    {}

    int App::run() noexcept
    {
        renderer->setClearColor(Colors::blue);

        while(!renderer->windowShouldClose())
        {
            BEGIN_MAIN_LOOP

            if(input->isJustPressed(Key::y)) logger.logInfo("Key is JUST pressed");
            if(input->isPressed(Key::y)) logger.logInfo("Key is pressed");
            if(input->isJustReleased(Key::y)) 
                logger.logInfo("Key is JUST released");

            renderer->drawFrame();

            input->update();

            glfwPollEvents();

            END_MAIN_LOOP
        }

        return 0;
    }
}