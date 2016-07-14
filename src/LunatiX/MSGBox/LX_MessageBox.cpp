
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
*	@file LX_MessageBox.cpp
*	@brief The message box Library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_MessageBox.hpp>


namespace LX_MSGBox
{

bool showMSG(Uint32 flag, const char *title, const char *msg, SDL_Window *w)
{
    return SDL_ShowSimpleMessageBox(flag,title,msg,w) == true;
}

};
