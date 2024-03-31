#include "app.hpp"
#include "external/glad.h"
#include "graphics/renderer.hpp"
#include "input.hpp"
#include "exception.hpp"
#include "graphics/voxel.hpp"
#include "graphics/primitives.hpp"
#include "app_options.hpp"

#define BEGIN_MAIN_LOOP try{
#define END_MAIN_LOOP }catch(Exception ex){logger.logError(ex.what());}

// initial window parameters
static constexpr u32 initialWindowWidth = 640u;
static constexpr u32 initialWindowHeight = 480u;
static const char* windowTitle = "VoxPrim editor";

namespace prim
{
    enum class AppState { Idle, MovingCamera, HoldingObject };

    App::App() : renderer(new Renderer(initialWindowWidth, initialWindowHeight, windowTitle)), input(new Input(renderer->getWindow())), 
        currentState(AppState::Idle)
    {}
    
    App::~App()
    {}

    int App::run()
    {
        renderer->setClearColor(Colors::green);

        Voxel voxel;
        voxel.transform.scale *= 3;
        voxel.transform.position.z -= 10.0f;
        voxel.albedo = Colors::blue;

        while(!renderer->windowShouldClose())
        {
            BEGIN_MAIN_LOOP

            //// Draw here ////
            voxel.draw(*renderer.get());
            ///////////////////

            renderer->endFrame();
            input->reset();
            glfwPollEvents();

            determineState();
            executeStateActions();

            END_MAIN_LOOP
        }

        return 0;
    }

    void App::determineState()
    {
        switch(currentState)
        {
            case AppState::Idle:
            {
                if(input->isPressed(MouseButton::right))
                {
                    currentState = AppState::MovingCamera;
                    renderer->setCursorMode(CursorMode::Disabled);
                }
            }
            case AppState::MovingCamera:
            {
                if(!input->isPressed(MouseButton::right))
                {
                    currentState = AppState::Idle;
                    renderer->setCursorMode(CursorMode::Normal);
                }
            }
            case AppState::HoldingObject:
            {
                break;
            }
        }
    }

    void App::executeStateActions()
    {
        switch(currentState)
        {
            case AppState::Idle:
            {
                break;
            }
            case AppState::MovingCamera:
            {
                Camera* camera = renderer->getCamera();
                float moveSpeedMultiplier = input->isPressed(AppOptions::cameraMoveMultiplierKey) ? AppOptions::cameraMoveSpeedMultiplier : 1.0f;
                camera->transform.position += camera->transform.right() * input->getAxis("Horizontal") * AppOptions::cameraMoveSpeed * moveSpeedMultiplier;
                camera->transform.position += camera->transform.backward() * input->getAxis("Vertical") * AppOptions::cameraMoveSpeed * moveSpeedMultiplier;
                glm::vec2 cursorDelta = input->getCursorDelta();
                camera->transform.rotation *= glm::quat(glm::vec3(-glm::radians(cursorDelta.y), 0.0f, 0.0f) * AppOptions::cameraRotationSpeed);
                camera->transform.rotation = glm::quat(glm::vec3(0.0f, -glm::radians(cursorDelta.x), 0.0f) * AppOptions::cameraRotationSpeed) 
                    * camera->transform.rotation;
                break;
            }
            case AppState::HoldingObject:
            {
                break;
            }
        }
    }
}