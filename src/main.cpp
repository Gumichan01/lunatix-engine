/*
    Main file for the demo
*/

#include <LunatiX/LX_Library.hpp>
#include <LunatiX/LX_Graphics.hpp>
#include <LunatiX/LX_Event.hpp>
#include <LunatiX/LX_Log.hpp>

#define UNUSED(X) (void)(X)


int main(int argc, char** argv)
{
    UNUSED(argc);UNUSED(argv);
    LX_AABB position = {0,0,256,256};
    LX_Event::LX_Input event;
    bool go = true;

    if(!LX_Init())
    {
        LX_Log::log("Cannot load the library: %s",LX_GetError());
        return -1;
    }

    // Information about how to build the window
    LX_Win::LX_WindowInfo info;
    LX_Win::LX_loadWindowConfig(info);
    info.w = 256;
    info.h = 256;

    LX_Win::LX_Window w(info);
    LX_Graphics::LX_Sprite sprite("data/bullet.png",w);

    while(go)
    {
        while(LX_Event::pollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                go = false;
                break;
            default:
                break;
            }
        }

        w.clearWindow();
        sprite.draw(&position);
        w.update();
        SDL_Delay(33);
    }

    LX_Quit();
    return 0;
}
