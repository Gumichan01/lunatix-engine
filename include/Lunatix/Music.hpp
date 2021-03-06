
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

/**
*   @file Music.hpp
*   @brief The music library
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <Lunatix/Sound.hpp>
#include <memory>


namespace libtagpp
{
class Tag;
}


namespace lx
{

namespace Graphics
{
class BufferedImage;
}

namespace Mixer
{

/**
*   @struct MusicTag
*   @brief High-level music metadata
*
*   MusicTag is a metadata structure that contains essential information
*   about a music (title, author, album, year, ...)
*
*   In comparison with *libtagpp::Tag*, MusicTag does not contain
*   low-level contents (track-gain, album-gain, bitrate, ...), but has
*   an image loaded from the audio file if it exists.
*/
struct MusicTag
{
    UTF8string title{""};                           /**< Title  */
    UTF8string artist{""};                          /**< Artist */
    UTF8string album{""};                           /**< Album  */
    UTF8string year{""};                            /**< Year (2016, 2014/02/01)         */
    UTF8string track{""};                           /**< Track number ("1", "01", "1/4") */
    UTF8string genre{""};                           /**< Genre  */
    UTF8string format{""};                          /**< Format (MP3, OGG, FLAC, M4A)    */
    UTF8string duration{""};                        /**< Duration, in HH:MM:SS format    */
    lx::Graphics::BufferedImage * img = nullptr;    /**< Album cover, if it exists  */

    ~MusicTag();
};

/**
*   @fn const MusicTag getMusicInfoFrom(const UTF8string& u8file) noexcept
*   Get information about the music file
*   @param [in] u8file the music file to get metadata from
*   @return The metadata
*
*   @sa MusicTag
*/
const MusicTag getMusicInfoFrom( const UTF8string& u8file ) noexcept;
/**
*   @fn const MusicTag getMusicInfoFrom(const std::string& file) noexcept;
*   Get information about the music file
*   @param [in] file the music file to get metadata from
*   @return The metadata
*
*   @sa MusicTag
*/
const MusicTag getMusicInfoFrom( const std::string& file ) noexcept;


class Music_;

/**
*   @class Music
*   @brief Class representing music
*   @note This can load WAVE, MOD, MIDI, OGG, MP3, FLAC files.
*/
class Music : public virtual Sound
{
    std::unique_ptr<Music_> m_mimpl;

    Music( const Music& m ) = delete;
    Music& operator =( const Music& m ) = delete;

public:

    /**
    *   @fn Music(const std::string& filename)
    *   @param [in] filename
    *   @exception MixerException On failure
    */
    Music( const std::string& filename );
    /**
    *   @fn Music(const UTF8string& filename)
    *   @param [in] filename
    *   @exception MixerException On failure
    */
    Music( const UTF8string& filename );

    /**
    *   @fn void fadeIn(int ms) noexcept
    *
    *   Fade in the current music over some milliseconds of time
    *
    *   @param [in] ms Milliseconds for the fade-in effect to complete
    *
    *   @note fadeIn starts playing the music with the fade-in effect.
    *         It is not necessary to call Music::play() if this function is called
    *
    *   @note Any previous music will be halted, or if it is fading out
    *         it will wait (blocking) for the fade to complete
    */
    void fadeIn( int ms ) noexcept;
    /**
    *   @fn void fadeInPos(int ms, int pos) noexcept
    *
    *   Fade in the current music over some milliseconds of time
    *
    *   @param [in] ms Milliseconds for the fade-in effect to complete
    *   @param [in] pos The position to start the music
    *
    *   @note fadeInPos starts playing the music with the fade-in effect.
    *         It is not necessary to call Music::play() if this function is called
    *
    *   @note Any previous music will be halted, or if it is fading out
    *         it will wait (blocking) for the fade to complete
    */
    void fadeInPos( int ms, int pos ) noexcept;
    /**
    *   @fn static void fadeOut(int ms) noexcept
    *
    *   Fade out the music over some milliseconds of time
    *
    *   @param [in] ms Milliseconds for the fade-out effect to complete
    *
    *   @note This functions works only when music is playing and
    *         no fading is already set to fade out
    */
    static void fadeOut( int ms ) noexcept;

    /**
    *   @fn virtual bool play() noexcept override
    *   Play the music
    *   @return TRUE on success, FALSE otherwise
    */
    virtual bool play() noexcept override;
    /**
    *   @fn bool play(bool infinite_loop) noexcept
    *   Play the music
    *   @param infinite_loop true for inifinite loop, false otherwise
    *   @return TRUE on success, FALSE otherwise
    */
    bool play( bool infinite_loop ) noexcept;
    /**
    *   @fn bool play(unsigned int loops) noexcept
    *   Play the music specified in the Music class
    *   @param [in] loops The loop constant
    *   @return TRUE on success,FALSE otherwise
    */
    bool play( unsigned int loops ) noexcept;
    /**
    *   @fn static void pause() noexcept
    *   Pause or resume the current music
    */
    static void pause() noexcept;
    /**
    *   @fn static void stop()
    *   Stop the music
    */
    static void stop() noexcept;

    /**
    *   @fn const libtagpp::Tag& getInfo() noexcept
    *   Get information about the current music
    *   @return The metadata
    *
    *   @note It provides low-level information about
    *   the file related to the music (bitrate, album-gain, ...)
    *
    *   @sa metaData()
    */
    const libtagpp::Tag& getInfo() noexcept;
    /**
    *   @fn const MusicTag& metaData() noexcept
    *   Get essential information about the current music
    *   @return The metadata
    *
    *   @sa MusicTag
    *   @sa getInfo()
    */
    const MusicTag& metaData() noexcept;

    ~Music();
};

}   // Mixer

}   // lx

#endif // MUSIC_H_INCLUDED
