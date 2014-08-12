#ifndef LX_AUDIO_H_INCLUDED
#define LX_AUDIO_H_INCLUDED



/*
*
*	Copyright (C)  Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*
*/

/**
*	@file LX_Audio.h
*	@brief The LX_Audio library, it will linked will the FMOD API
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 18th, 2014
*
*/


#include<cstdio>
#include<cstdlib>

#include<iostream>

#include<SDL/SDL.h>
#include<SDL/SDL_mixer.h>

#include "LX_error.h"

/// @todo Support of 2D sound effects

#define LX_AUDIO_STEREO_SOUND 2             /**< The stereo variable the mix module */
#define LX_AUDIO_MONO_SOUND 1               /**< The mono variable for the mix module */
#define LX_AUDIO_DEFAULT_CHUNKSIZE 1024     /**< The default chunsize for the mix module */

#define LX_AUDIO_LOOP -1                    /**< The audio LOOP variable */

/**
*   @class LX_Audio
*   @brief The Target Xplosion sound engine
*
*   This SDL_Mixer-based sound engine will load and read a various audio files.
*
*
**/
class LX_Audio{

    Mix_Music *music;      /**<The music you want to play (note : LX_Audio only plays one music)*/


    public:

/**
*   @fn LX_Audio()
*
*   Load the LX_Audio library
*
**/
    LX_Audio()
    {

        int err = 0;

        err = Mix_Init(MIX_INIT_OGG);

        if(err == -1)
        {
            fprintf(stderr,"\nException occured in LX_Audio constructor, Mix_Init : %s \n", Mix_GetError());
            throw LX_AUDIO_INIT_ERROR;
        }

        err = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,LX_AUDIO_STEREO_SOUND,LX_AUDIO_DEFAULT_CHUNKSIZE);

        if( err < 0)
        {
            fprintf(stderr,"\nException occured in LX_Audio constructor, Mix_OpenAudio : %s \n", Mix_GetError());
            throw LX_AUDIO_OPEN_ERROR;
        }

        music = NULL;

    }

    bool load_music(std::string filename);
    bool play_music();
    void pause_music();
    void stop_music();

    /* [TYPE] load_sample(std::string filename);
    [TYPE] read_sample([TYPE] *sample); */


    ~LX_Audio()
    {
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        Mix_Quit();
    }

};

#endif // LX_AUDIO_H_INCLUDED



















