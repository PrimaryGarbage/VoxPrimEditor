#ifndef __APP_HPP__
#define __APP_HPP__

#include "typedefs.hpp"
#include "logger.hpp"


namespace prim
{
    // forward declaration
    class Renderer;
    class Input;

    class App
    {
    private:
        Unp<Renderer> renderer;
        Unp<Input> input;
        Logger logger;
    public:
        App();
        ~App();

        int run() noexcept;
    };
}


#endif // __APP_HPP__