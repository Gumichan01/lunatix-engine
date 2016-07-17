#ifndef LX_CHUNK_H_INCLUDED
#define LX_CHUNK_H_INCLUDED

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
*	@file LX_Chunk.hpp
*	@brief The chunk header
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include "LX_Sound.hpp"


struct Mix_Chunk;

namespace LX_FileIO
{

class LX_FileBuffer;

};

/// TODO Implements bool play(int channel,int loops);
/// TODO Implements bool play(int channel,int loops,int ticks);

namespace LX_Mixer
{

/**
*   @class LX_ChunkException
*   @brief The exception class of LX_Chunk
*/
class LX_ChunkException : public std::exception
{
    std::string _string_error;

public :

    /// Construct the exception
    LX_ChunkException(std::string err);
    /// Construct the exception by copy
    LX_ChunkException(const LX_ChunkException& me);

    /// Get the error message
    const char * what() const noexcept;

    /// Destroy the exception
    ~LX_ChunkException() noexcept;
};


/**
*   @class LX_Chunk
*   @brief The chunk class
*/
class LX_Chunk : public virtual LX_Sound
{
    Mix_Chunk *_chunk;

    LX_Chunk(LX_Chunk& m);
    LX_Chunk& operator =(LX_Chunk& m);

public:

    /**
    *   @fn LX_Chunk(Mix_Chunk *sample)
    *
    *   Construct the instance setting the Mix_Chunk instance
    *
    *   @param sample The sample file
    */
    LX_Chunk(Mix_Chunk *sample); /// TODO remove this constructor (Mix_Chunk)

    /**
    *   @fn LX_Chunk(std::string filename)
    *
    *   Construct the instance creating the Mix_Chunk instance from a file
    *
    *   @param filename The file to create the chunk from
    *
    *   @note It is preferable to give a .wav file to the constructor.
    *           The chunk was optimized for this format. But it can work with
    *           an other file type.
    *
    *   @exception LX_ChunkException if the chunk cannot be created from the file
    */
    LX_Chunk(std::string filename);

    /**
    *   @fn LX_Chunk(LX_FileIO::LX_FileBuffer * file)
    *
    *   Construct the instance creating the Mix_Chunk instance
    *   from a file buffer.
    *
    *   @param file The file buffer to create the chunk from
    *   @exception LX_ChunkException if the chunk cannot be created from the file buffer
    */
    LX_Chunk(LX_FileIO::LX_FileBuffer *file);

    /**
    *   @fn bool load(std::string filename)
    *
    *   Load the WAV sample from a file
    *
    *   @param filename The name of the sample file
    *
    *   @return TRUE on success, FALSE otherwise
    *   @sa loadFromBuffer
    */
    bool load(std::string filename);    /// TODO remove this function (useless)

    /**
    *   @fn bool loadFromBuffer(LX_FileBuffer *file)
    *
    *   Load the sample from a file buffer
    *
    *   @param file The file buffer to load the chunk from
    *   @return TRUE on success, FALSE otherwise
    */
    bool loadFromBuffer(LX_FileIO::LX_FileBuffer *file);

    /**
    *   @fn bool play()
    *
    *   Play the current sample
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note This function plays the sample on the first unserved channel
    *         with the no loop option
    */
    bool play();

    /**
    *   @fn bool play(int channel)
    *
    *   Play the current sample
    *
    *   @param channel The channel to play the chunk on
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note This function plays the sample with no loop
    */
    bool play(int channel);

    /**
    *   @fn bool play(int channel,int ticks)
    *
    *   Play the current sample during a moment
    *
    *   @param channel The channel to play the chunk on
    *   @param ticks The limit in millisecond to play the current sample
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note This function plays the sample on with no loop
    */
    bool play(int channel,int ticks);

    /**
    *   @fn int volume(int newVolume)
    *
    *   Set the volume of the chunk, from 0 to 128
    *
    *   @param newVolume The volume to set
    *   @return The previous volume setting
    *
    *   @note If the volume is less than 0, then the previous volume is the current volume
    *           and there is no change
    *   @note If the new volume is greater than 128, the volume is set to 128
    *   @note 128 is the maximum value defined by the MIX_MAX_VOLUME macro
    *
    */
    int volume(int newVolume);

    /**
    *   @fn ~LX_Chunk()
    *   Destroy the instance
    */
    ~LX_Chunk();
};

};

#endif // LX_CHUNK_H_INCLUDED
