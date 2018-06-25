
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

/**
*   @file Music.cpp
*   @brief The implementation of the music library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/Music.hpp>
#include <Lunatix/Error.hpp>
#include <Lunatix/Texture.hpp>
#include <Lunatix/FileBuffer.hpp>
#include <Lunatix/utils/libtagspp/libtagspp.hpp>
#include <SDL2/SDL_mixer.h>


namespace
{

const int LX_NOLOOP  = 0;
const int LX_INFLOOP = -1;


LX_Graphics::
LX_BufferedImage * _loadImage( const std::string& file,
                               const libtagpp::ImgMetaData& imgdata )
{
    if ( imgdata._img_offset <= 0 && imgdata._img_size <= 0 )
        return nullptr;

    const size_t IMG_OFFSET = static_cast<size_t>( imgdata._img_offset );
    const size_t IMG_SZ     = static_cast<size_t>( imgdata._img_size );

    return LX_FileIO::LX_FileBuffer( file, IMG_OFFSET, IMG_SZ ).loadBufferedImage();
}

}   // namespace

namespace LX_Mixer
{

/* Music tag */

LX_MusicTag::~LX_MusicTag()
{
    delete img;
}


const LX_MusicTag getMusicInfoFrom( const UTF8string& u8file ) noexcept
{
    return getMusicInfoFrom( u8file.utf8_sstring() );
}

const LX_MusicTag getMusicInfoFrom( const std::string& file ) noexcept
{
    libtagpp::Tag tag;
    LX_MusicTag mtag;

    if ( !tag.readTag( file ) )
        LX_setError( std::string( "Cannot get metadata from " ) + file );

    mtag.title    = tag.title();
    mtag.artist   = tag.artist();
    mtag.album    = tag.album();
    mtag.year     = tag.year();
    mtag.track    = tag.track();
    mtag.genre    = tag.genre();
    mtag.format   = tag.properties().format;
    mtag.duration = tag.properties().duration;
    mtag.img      = _loadImage( file, tag.getImageMetaData() );

    return mtag;
}


/* LX_music: private implementation */

class LX_Music_
{
    Mix_Music * _music = nullptr;
    std::string _filename{};
    libtagpp::Tag _tag;
    LX_MusicTag _mtag;
    bool mtag_set = false;

    LX_Music_( const LX_Music_& m ) = delete;
    LX_Music_& operator =( const LX_Music_& m ) = delete;

    void load_( const std::string& filename )
    {
        Mix_FreeMusic( _music );
        _music = Mix_LoadMUS( filename.c_str() );

        if ( _music == nullptr )
            throw LX_MixerException( "LX_Music — Cannot load " + filename );
    }

public:

    explicit LX_Music_( const std::string& filename )
        : _music( nullptr ), _filename( filename ), _tag(), _mtag(), mtag_set( false )
    {
        load_( filename );
    }

    explicit LX_Music_( const UTF8string& filename )
        : LX_Music_( filename.utf8_sstring() ) {}

    void fadeIn( int ms ) noexcept
    {
        Mix_FadeInMusic( _music, LX_NOLOOP, ms );
    }

    void fadeInPos( int ms, int pos ) noexcept
    {
        Mix_FadeInMusicPos( _music, LX_NOLOOP, ms, pos );
    }

    bool play() noexcept
    {
        return play( false );
    }

    bool play( bool infinite ) noexcept
    {
        return Mix_PlayMusic( _music, infinite ? LX_INFLOOP : LX_NOLOOP ) == 0;
    }

    bool play( unsigned int loops ) noexcept
    {
        return Mix_PlayMusic( _music, static_cast<int>( loops ) ) == 0;
    }

    const libtagpp::Tag& getInfo() noexcept
    {
        if ( !_tag.readTag( _filename.c_str() ) )
            LX_setError( "Cannot get metadata" );

        return _tag;
    }

    const LX_MusicTag& metaData() noexcept
    {
        if ( !mtag_set )
        {
            getInfo();
            _mtag.title    = _tag.title();
            _mtag.artist   = _tag.artist();
            _mtag.album    = _tag.album();
            _mtag.year     = _tag.year();
            _mtag.track    = _tag.track();
            _mtag.genre    = _tag.genre();
            _mtag.format   = _tag.properties().format;
            _mtag.duration = _tag.properties().duration;
            _mtag.img      = _loadImage( _filename, _tag.getImageMetaData() );
            mtag_set       = true;
        }

        return _mtag;
    }

    ~LX_Music_()
    {
        Mix_FreeMusic( _music );
    }
};

/* LX_Music: public functions */
LX_Music::LX_Music( const std::string& filename )
    : _mimpl( new LX_Music_( filename ) ) {}

LX_Music::LX_Music( const UTF8string& filename )
    : _mimpl( new LX_Music_( filename ) ) {}


void LX_Music::fadeIn( int ms ) noexcept
{
    _mimpl->fadeIn( ms );
}

void LX_Music::fadeInPos( int ms, int pos ) noexcept
{
    _mimpl->fadeInPos( ms, pos );
}

void LX_Music::fadeOut( int ms ) noexcept
{
    Mix_FadeOutMusic( ms );
}


bool LX_Music::play() noexcept
{
    return _mimpl->play();
}

bool LX_Music::play( bool infinite_loop ) noexcept
{
    return _mimpl->play( infinite_loop );
}

bool LX_Music::play( unsigned int loops ) noexcept
{
    return _mimpl->play( loops );
}


void LX_Music::pause() noexcept
{
    if ( Mix_PausedMusic() )
        Mix_ResumeMusic();
    else
        Mix_PauseMusic();
}

void LX_Music::stop() noexcept
{
    if ( Mix_PlayingMusic() )
        Mix_HaltMusic();
}


const libtagpp::Tag& LX_Music::getInfo() noexcept
{
    return _mimpl->getInfo();
}

const LX_MusicTag& LX_Music::metaData() noexcept
{
    return _mimpl->metaData();
}

LX_Music::~LX_Music()
{
    _mimpl.reset();
}

}