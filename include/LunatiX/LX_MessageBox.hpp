#ifndef LX_MESSAGEBOX_HPP_INCLUDED
#define LX_MESSAGEBOX_HPP_INCLUDED


/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_MessageBox.hpp
*	@brief The message box Library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <SDL2/SDL_messagebox.h>

#define LX_MSG_ERR  SDL_MESSAGEBOX_ERROR        /**< Error message          */
#define LX_MSG_WARN SDL_MESSAGEBOX_WARNING      /**< Warning message        */
#define LX_MSG_INFO SDL_MESSAGEBOX_INFORMATION  /**< Information message    */


/**
*   @namespace LX_MSGBox
*   @brief The Message Box module
*/
namespace LX_MSGBox
{

/**
*   @fn int showMSG(Uint32 flag, const char *title, const char *msg, SDL_Window *w)
*
*   Display a simple message box
*
*   @param flag One of these following flags:
*           - LX_MSG_ERR : Error megssage
*           - LX_MSG_WARN : Warning message
*           - LX_MSG_INFO : Information message
*   @param title The title of the box, UTF-8 format
*   @param msg The text to display in the box, UTF-8 format
*   @param w The parent window, or a null pointer for no parent
*
*   @return TRUE on success, FALSE on error
*/
bool showMSG(Uint32 flag, const char *title, const char *msg, SDL_Window *w);

};

#endif // LX_MESSAGEBOX_HPP_INCLUDED
