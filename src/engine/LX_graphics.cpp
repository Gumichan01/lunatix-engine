

/*
*	Copyright (C) 2014 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_graphics.cpp
*	@brief The LunatiX_engine graphic module
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date January 18th, 2015
*
*
*/
#include "LX_graphics.h"
#include "LX_windowManager.h"


static LX_graphics *gInstance = NULL;

/**
*   @fn LX_graphics * LX_graphics::getInstance()
*
*   Get the unique instance of the LX_graphics class
*
*   @return the unique instance of LX_graphics
*
*/
LX_graphics * LX_graphics::getInstance()
{
    if(gInstance == NULL)
    {
        try
        {
            gInstance = new LX_graphics();
        }
        catch(std::exception & g_ex)
        {
            std::cerr << "exception occured in LX_graphics::getInstance : " << g_ex.what() << std::endl;
            return NULL;
        }
    }

    return gInstance;
}


/**
*
*   @fn void LX_graphics::destroy()
*
*   Destroy the unique instance
*
*   @warning you must call this function to prevent a memory leak if you called LX_graphics::getInstances()
*
*/
void LX_graphics::destroy()
{
    delete gInstance;
    gInstance = NULL;
}


/**
*   @fn LX_graphics::LX_graphics()
*
*   Create the instance
*/
LX_graphics::LX_graphics()
{
    mainWindow = new LX_window();

    //window = mainWindow->getWindow();
    //surface = mainWindow->getSurface();
    renderer = SDL_CreateRenderer(mainWindow->getWindow(),-1,SDL_RENDERER_ACCELERATED);

    if(renderer == NULL)
        std::cerr << "renderer is not set : " << SDL_GetError() << std::endl;

}


/**
*   @fn LX_graphics::~LX_graphics()
*
*   Destroy the instance
*
*/
LX_graphics::~LX_graphics()
{
    delete mainWindow;
    mainWindow = NULL;

}



/**
*
*   @fn SDL_Surface * LX_graphics::loadSurfaceFromBMP(std::string filename)
*
*   This function loads an SDL_Surface from a .bmp file an optimizes its format
*
*   @param filename : the .bmp file name which describe the image
*
*   @return the loaded and optimized surface if there is no problem, NULL otherwise
*
*   @warning If you try to load an other image file with this function, it will fail.
*
*/
SDL_Surface * LX_graphics::loadSurfaceFromBMP(std::string filename)
{
    SDL_Surface *loaded = NULL;
    SDL_Surface *optimized = NULL;

    loaded = SDL_LoadBMP(filename.c_str());

    if(loaded == NULL)
    {
        std::cerr << "Error occurred in LX_graphics::load_surfaceFromBMP : " << SDL_GetError() << std::endl;
        return NULL;
    }

    //optimized = SDL_DisplayFormat(loaded);
    optimized = SDL_ConvertSurface(loaded,mainWindow->getSurface()->format,0x00000000);

    SDL_FreeSurface(loaded);

    return optimized;
}


/**
*
*   @fn SDL_Surface * LX_graphics::loadSurface(std::string filename)
*
*   This function loads an SDL_Surface from any image file an optimized its format
*
*   @param filename : the file name which describe the image
*
*   @return the loaded and optimized surface if there is no problem, NULL otherwise
*
*   @note You may use this function instead of load_surfaceFromBMP() to load a non .bmp file
*   @note If you want to load a .bmp file and use the transparency,
*           please use load_surfaceFromBMP and set_alpha()
*
*   @warning When you call this function, the format optimization includes the alpha canal.
*               No alpha needs to be set on the surface after that, except if you want to modify it
*
*/
SDL_Surface * LX_graphics::loadSurface(std::string filename)
{
    SDL_Surface *loaded = NULL;
    SDL_Surface *optimized = NULL;

    loaded = IMG_Load(filename.c_str());

    if(loaded == NULL)
    {
        std::cerr << "Error occurred in LX_graphics::load_surface : " << SDL_GetError() << std::endl;
        return NULL;
    }

    //std::cerr << "optimize " << std::endl;
    //optimized = SDL_DisplayFormatAlpha(loaded);
    optimized = SDL_ConvertSurface(loaded,mainWindow->getSurface()->format,0x00000000);

    SDL_FreeSurface(loaded);

    return optimized;
}


/**
*   @fn SDL_Texture * LX_graphics::loadTextureFromSurface(SDL_Surface *target)
*
*   Loads create a texture from a surface
*
*   @param target : the surface you want to use to create the texture
*
*   @return  a new pointer to the texture if the loading is successful, NULL otherwise
*
*   @note : if target is NULL, the fonction returns immediately a NULL value
*
*/
SDL_Texture * LX_graphics::loadTextureFromSurface(SDL_Surface *target)
{
    SDL_Texture *newTexture = NULL;

    if( target == NULL)
    {
        std::cerr << "LX_graphics::loadTextureFromSurface : the surface is NULL" << std::endl;
        return NULL;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer,target);

    if( newTexture == NULL )
    {
        std::cerr << "Error occurred in LX_graphics::loadTextureFromSurface : " << SDL_GetError() << std::endl;
        return NULL;
    }

    return newTexture;
}



/**
*
*   @fn bool LX_graphics::set_alpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue)
*
*   This function set the alpha value on a SDL_surface
*
*   @param image : the surface
*   @param red : the the red color canal of the future transparent color
*   @param green : the the green color canal of the future transparent color
*   @param blue : the the blue color canal of the future transparent color
*
*   @return TRUE if the transparency was done without problem, FALSE otherwise
*
*   @note You may use any format for values (hexadecimal, digital,...).
*
*/
bool LX_graphics::set_alpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue)
{   // It is better to deal with Uint8 variables instead of an unsigned int

    Uint32 colorkey = SDL_MapRGB(image->format,red,green,blue);

    int err = SDL_SetColorKey(image,SDL_TRUE, colorkey);    // SDL_TRUE replaced the old flags

    if(err == -1)
    {
        std::cerr << "Error occurred in LX_graphics::set_alpha : " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}


/**
*   @fn int LX_graphics::addWindow(SDL_Window *win)
*
*   Adds a SDL_Window to the window manager
*
*   @param win : the window you want to add
*
*   @return a positive value that match with the index of the window in the vector,
*            -1 if win is NULL, or -2 if an internal problem occurs
*
*/
int LX_graphics::addSDLWindow(LX_window *win)
{   ///@todo [vector] Implement the window insertion
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"LX_graphics::addSDLWindow","Not implemented yet",NULL);
    return -1;
}


/**
*   @fn int bool LX_graphics::destroySDLWindow(int wd)
*
*   @param win : The window descriptor
*
*   @return true if there no problem, false otherwise
*
*/
bool LX_graphics::destroySDLWindow(unsigned int wd)
{
    ///@todo [vector] Implement the window destruction

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"LX_graphics::destroySDLWindow","Not implemented yet",NULL);

    return false;
}


/**
*
*   @fn void LX_graphics::put_surface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
*
*   This function puts the surface on the main surface according to its position and the area to put on it
*
*   @param image : the surface to put
*   @param area : the area of the surface to put on the screen
*   @param pos : the position of what you want to put
*
*   @note If you do not need to determine the area parameter of the surface, put NULL
*
*   @return TRUE if the image was put with success, FALSE otherwise
*/
bool LX_graphics::put_surface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
{
    int err = 0;
    SDL_Rect offset;

    // I check if the image or the position is NULL
    if(image == NULL)
    {
        std::cerr << "Error occurred in LX_graphics::put_surface : the surface to blit is NULL " << std::endl;
        return false;
    }

    /*if(surface == NULL)
    {
        std::cerr << "Error occurred in LX_graphics::put_surface :  the main surface is NULL" << std::endl;
        return false;
    }*/

    if(pos == NULL)
    {   // The texture will be set on the top-left of the main surface
        offset.x = 0;
        offset.y = 0;
    }
    else
    {
        offset.x = pos->x;
        offset.y = pos->y;
    }

    err = SDL_BlitSurface(image,area,mainWindow->getSurface(),&offset);

    if(err < 0)
    {
        std::cerr << "Error occurred in LX_graphics::put_surface : " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}


/**
*   @fn bool LX_graphics::putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos)
*
*   This function puts the texture on the main window according to its position and the area to put on it
*
*   @param origin : the texture to put
*   @param area : the area of the surface to put on the renderer
*   @param pos : the position of what you want to put
*
*   @note If you do not need to determine the area parameter of the surface, put NULL
*   @warning The width and the height defined in the SDL_Rect are important, the function uses it
*               to display the texture according to its dimension
*
*   @return TRUE if the texture was put with success, FALSE otherwise
**/
bool LX_graphics::putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos)
{
    if(SDL_RenderCopy(renderer,origin,area,pos) < 0)
    {
        std::cerr << "Error in LX_graphics::putTexture: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}



/**
*   @fn void LX_graphics::updateMainRenderer()
*
*   Updates the main renderer
*
*/
void LX_graphics::updateMainRenderer()
{
    SDL_RenderPresent(renderer);
}


/**
*
*   @fn void LX_graphics::updateMainWindow()
*
*   This function updates the main window
*
*/
void LX_graphics::updateMainWindow()
{
    SDL_UpdateWindowSurface(mainWindow->getWindow());
}

/**
*
*   @fn void LX_graphics::clearMainWindow()
*
*   This function clears the main window
*
*/
void LX_graphics::clearMainWindow()
{
    SDL_FillRect(mainWindow->getSurface(),NULL, SDL_MapRGB(mainWindow->getSurface()->format,0,0,0));
}




























