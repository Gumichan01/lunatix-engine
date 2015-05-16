#ifndef LX_WINDOW_H_INCLUDED
#define LX_WINDOW_H_INCLUDED



/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Window.hpp
*	@brief The LX_Window library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.4
*
*/


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;


#define LX_GRAPHICS_FULLSCREEN_DESKTOP SDL_WINDOW_FULLSCREEN_DESKTOP    /**< Fullscreen with desktop resolution */
#define LX_GRAPHICS_FULLSCREEN SDL_WINDOW_FULLSCREEN                    /**< Fullscreen mode with original resolution */
#define LX_GRAPHICS_NO_FULLSCREEN 0                                     /**< Original resolution in window */

#define LX_WINDOW_SURFACE 0x01                                          /**< Use surface */
#define LX_WINDOW_RENDERING 0x10                                        /**< Use Rendering */
#define LX_WINDOW_DEFAULT_MODE LX_WINDOW_RENDERING                      /**< Default mode (Rendering) */



namespace LX_Graphics{


    /**
    *   @class LX_WindowException
    *   @brief The exception class of LX_Window
    *
    *   This class describes the exception occured when the window initialization fails.
    *
    */
    class LX_WindowException : public std::exception
    {
        std::string str_err;

        public :

        LX_WindowException(std::string err);

        const char * what() const throw();

        ~LX_WindowException() throw();
    };



    /**
    *   @class LX_Window
    *   @brief The LX_Window class.
    *
    *   This class describes the window.
    *
    *   @note By default, the constructor of the LX_window class gets informations
    *          from the configuration file
    *
    *   @warning The LX_Window class must be defined only after you initialized the engine (calling LX_Init())
    *   @warning A LX_WindowException may be occured if the window creation fails
    *
    */
    class LX_Window{

        SDL_Window *window;     /**< The internal window structure */
        SDL_Renderer *renderer; /**< The main renderer */

        int originalWidth;      /**< The width of the window */
        int originalHeight;     /**< The height of the window */

        void init(std::string title, int posX, int posY, int w, int h, const Uint32 mode, Uint32 flag);
        void init2();

        public :

        LX_Window(const Uint32 mode);
        LX_Window(SDL_Window *sdlWin, const Uint32 mode);
        LX_Window(std::string title, const Uint32 mode);
        LX_Window(std::string title, int posX, int posY, int w, int h,
                    const Uint32 mode, const Uint32 flag);

        void setTitle(std::string title);

        // Put the sprite on the screen
        bool putSurface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos);
        bool putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos);
        bool putTextureAndRotate(SDL_Texture *origin, const SDL_Rect *area, const SDL_Rect *pos,
                        const double angle);

        void setWindowSize(int w, int h);
        void setFullscreen(Uint32 flag);

        // Update and clearing window
        void updateWindow();
        void updateRenderer();

        void clearWindow();
        void clearRenderer();

        SDL_Renderer * getRenderer();
        SDL_Surface * getSurface();
        SDL_Window * getWindow();

        int getWidth();
        int getHeight();


        ~LX_Window();
    };

};

#endif // LX_WINDOW_H_INCLUDED














