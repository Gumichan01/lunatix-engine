#ifndef LX_MIXER_H_INCLUDED
#define LX_MIXER_H_INCLUDED



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
*	@file LX_Mixer.hpp
*	@brief The mixer library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.4
*
*/

#include <SDL2/SDL_mixer.h>

#define LX_MIXER_STEREO_SOUND 2             /**< The stereo variable the mix module */
#define LX_MIXER_MONO_SOUND 1               /**< The mono variable for the mix module */
#define LX_MIXER_DEFAULT_CHUNKSIZE 1024     /**< The default chunsize for the mix module */

#define LX_MIXER_LOOP -1                    /**< Activate the loop */
#define LX_MIXER_NOLOOP 0                   /**< No loop is activated */

#define LX_MIXER_EFFECT_LOUD 255            /**< Loud (for effect functions) */
#define LX_MIXER_EFFECT_SILENCE 0           /**< Silence (for effect functions) */
#define LX_MIXER_EFFECT_NO_DISTANCE 0       /**< The distance between the source and the listener */
#define LX_MIXER_EFFECT_NO_ANGLE 0          /**< The angle bteween the source and the front */



class LX_Music;
class LX_Chunk;

/**
*   @namespace LX_Mixer
*   @brief The mixer module of LunatiX Engine
*
*   This SDL_Mixer-based sound engine will load and read a various audio files
*
**/
namespace LX_Mixer{


    /* == Music and chunk == */
    LX_Music * loadMusic(std::string filename);
    LX_Music * loadMusic(Mix_Music *mus);

    LX_Chunk * loadSample(std::string filename);
    LX_Chunk * loadSample(Mix_Chunk *ch);

    int allocateChannels(int num);
    int reserveChannels(unsigned int num);
    int channelVolume(int channel,int volume);
    void pause(int channel);
    void resume(int channel);
    void haltChannel(int channel);
    void expireChannel(int channel, int ticks);
    int isPlaying(int channel);
    int isPaused(int channel);


    /* == Effects == */

    // Fading
    void fadeInMusic(LX_Music *music,int ms);
    void fadeOutMusic(int ms);

    // Panning
    void setPanning(int channel,Uint8 left,Uint8 right);
    void removePanning(int channel);

    // 3D Position
    void setPosition(Sint16 angle);
    void setPosition(Sint16 angle, int distance);
    void setPosition(int channel, Sint16 angle, int distance);
    void resetPosition(int channel);

    // Reverse stereo
    void reverseStereo(int channel,int flip);

    // Distance
    void setDistance(Uint8 distance);
    void setDistance(int channel,Uint8 distance);

};



#endif // LX_MIXER_H_INCLUDED
















