
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


#include <LunatiX/LX_Sync.hpp>
#include <LunatiX/LX_Log.hpp>
#include <SDL2/SDL_mutex.h>


namespace LX_Multithreading
{

LX_Mutex::LX_Mutex() : _mutex(SDL_CreateMutex())
{
    if(_mutex == nullptr)
        LX_Log::logCritical(LX_Log::LX_LOG_APPLICATION,"Broken mutex");
}


void LX_Mutex::lock()
{
    SDL_LockMutex(_mutex);
}


void LX_Mutex::unlock()
{
    SDL_UnlockMutex(_mutex);
}


LX_Mutex::~LX_Mutex()
{
    SDL_DestroyMutex(_mutex);
}

};
