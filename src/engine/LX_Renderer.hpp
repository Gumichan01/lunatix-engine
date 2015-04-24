#ifndef LX_GRAPHICS_H_INCLUDED
#define LX_GRAPHICS_H_INCLUDED



/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Renderer.hpp
*	@brief The LX_Renderer library, it will be linked with the SDL library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date January 28th, 2015
*
*
*/

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "LX_Window.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;


#define LX_GRAPHICS_FULLSCREEN_DESKTOP SDL_WINDOW_FULLSCREEN_DESKTOP    /** < Fullscreen with desktop resolution */
#define LX_GRAPHICS_FULLSCREEN SDL_WINDOW_FULLSCREEN                    /** < Just fullscreen mode with original resolution */
#define LX_GRAPHICS_NO_FULLSCREEN 0                                     /** < Original resolution in window */


namespace LX_Graphics{


    /**
    *   @class LX_Renderer
    *   @brief The LunatiX_engine graphic module.
    *
    *   This class describes the LX_Renderer engine.
    *
    *   @note : The LX_Renderer class uses an instance of LX_Window
    *           to get the main window information
    *   @warning Because of the LX_Window and ht use of SDL functions,
    *   LX_Renderer class must be built only after you initialized LX_engine (calling LX_Init())
    *
    */
    class LX_Renderer{

        LX_Graphics::LX_Window *mainWindow;     /**< The main window */
        SDL_Renderer *renderer;                 /**< The main renderer */

        int originalWidth;
        int originalHeight;

        LX_Renderer();
        LX_Renderer(LX_Graphics::LX_Window *win);

        void init();

        public:

        // Get the instance
        static LX_Renderer * createInstance();
        static LX_Renderer * createInstance(LX_Graphics::LX_Window * win);
        static LX_Renderer * getInstance();
        static void destroy();


        SDL_Surface * loadSurface(std::string filename);

        SDL_Texture * loadTextureFromSurface(SDL_Surface *target);
        SDL_Texture * loadTextureFromFile(std::string filename);

        bool set_alpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue);

        // put the sprite on the screen
        bool put_surface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos);
        bool putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos);

        void setWindowSize(int w, int h);
        void setFullscreen(Uint32 flag);

        // the update and clearing functions
        void updateWindow();
        void updateRenderer();

        void clearWindow();
        void clearRenderer();

        SDL_Surface * getSurface();
        SDL_Renderer * getRenderer();

        ~LX_Renderer();

    };

};

#endif // LX_GRAPHICS_H_INCLUDED












