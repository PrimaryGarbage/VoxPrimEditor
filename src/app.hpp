#ifndef __APP_HPP__
#define __APP_HPP__

#include "typedefs.hpp"
#include "logger.hpp"


namespace prim
{
    // forward declaration
    class Renderer;
    class Input;
    enum class AppState;

    class App
    {
    private:
        Unp<Renderer> renderer;
        Unp<Input> input;
        Logger logger;
        AppState currentState;

        void determineState();
        void executeStateActions();
    public:
        App();
        ~App();

        int run();
    };
}


#endif // __APP_HPP__