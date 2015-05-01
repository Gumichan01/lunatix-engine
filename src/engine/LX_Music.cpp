

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
*	@file LX_Music.cpp
*	@brief The LX_Music implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*
*/


#include "LX_Sound.hpp"
#include "LX_Music.hpp"
#include "LX_Error.hpp"




/**
*   @fn LX_Music::LX_Music()
*
*   Load the LX_Music manager
*
*/
LX_Music::LX_Music()
{
    music = NULL;
}


/**
*   @fn LX_Music::LX_Music(Mix_Music *mus)
*
*   Load the LX_Music manager with a Mix_Music
*
*   @param mus The Mix_Music
*
*/
LX_Music::LX_Music(Mix_Music *mus)
{
    music = mus;
}


/**
*   @fn LX_Music::LX_Music(std::string filename)
*
*   Load the LX_Music manager with a Mix_Music
*
*   @param filename The music filename you want to load
*
*/
LX_Music::LX_Music(std::string filename)
{
    music = NULL;

    load(filename.c_str());
}


/**
*   @fn LX_Music::~LX_Music()
*
*   Destroy the instance
*
*/
LX_Music::~LX_Music()
{
    Mix_FreeMusic(music);
}



/**
*   @fn bool LX_Music::load(std::string filename)
*
*   Load the music specified in the music file
*
*   @param filename The file to load the music from
*
*   @return TRUE on success, FALSE otherwise
*
*/
bool LX_Music::load(std::string filename)
{
    Mix_FreeMusic(music);

    music = Mix_LoadMUS(filename.c_str());

    if(music == NULL)
        return false;

    return true;
}


/**
*   @fn int LX_Music::play(int loops)
*
*   Play the music specified in the LX_Music class
*
*   @param loops The loop constant
*
*   @return 0 on success, -1 otherwise
*
*/
int LX_Music::play(int loops)
{
    return Mix_PlayMusic(music,loops);
}


/**
*   @fn int LX_Music::play()
*
*   Play the music specified in the LX_Music class
*
*   @return 0 on success, -1 otherwise
*
*   @note This function internally calls play(int loops) with no loop
*
*/
int LX_Music::play()
{
    return play(0);
}


/**
*   @fn void LX_Music::pause()
*
*   Pause or resume the current music
*
*/
void LX_Music::pause()
{
    if(Mix_PausedMusic())
    {
        Mix_ResumeMusic();
    }
    else
    {
        Mix_PauseMusic();
    }
}


/**
*   @fn void LX_Music::stop()
*
*   Stop the music
*
*/
void LX_Music::stop()
{
    if(Mix_PlayingMusic())
    {
        Mix_HaltMusic();
    }
}



/**
*   @fn int LX_Music::volume(int newVolume)
*
*   Set the music volume to newVolume, from 0 to 128
*
*   @param newVolume The volume to set
*
*   @return The previous volume setting
*
*   @note If the volume is equals to -1, then the previous volume is the current volume
*   @note If the new volume is greater than 128, the volume is set to 128
*   @note The value 128 is the maximum value defined by the MIX_MAX_VOLUME macro
*
*/
int LX_Music::volume(int newVolume)
{
    return Mix_VolumeMusic(newVolume);
}



/**
*   @fn Mix_Music * LX_Music::getMusic()
*
*   Return the instance to the SDL_Music structure
*
*   @return The Mix_Music
*
*/
Mix_Music * LX_Music::getMusic()
{
    return music;
}



















