
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
*   @file Log.cpp
*   @brief The Log file
*   @author Luxon Jean-Pierre(Gumichan01)
*/

#include <Lunatix/Log.hpp>
#include <sstream>
#include <ctime>

#if defined(__WIN32__)
#include <Windows.h>
#elif defined(__linux__)
#include <cmath>
#else
#error "Not supported system"
#endif

namespace
{

// Get the time in millisecond
long getMillisTime() noexcept
{
    long ms;

#if defined(__WIN32__)  // Windows

    SYSTEMTIME st;
    GetSystemTime( &st );
    ms = static_cast<long>( st.wMilliseconds );

#elif defined(linux) || defined(__linux) || defined(__linux__)  // Unix/Linux

    struct timespec t;
    clock_gettime( CLOCK_REALTIME, &t );
    ms = static_cast<long>( std::round( static_cast<double>( t.tv_nsec ) / 1.0e6 ) );

#else   // Other system
#error "Unrecognized operating system"
#endif

    return ms;
}

std::string getDate() noexcept
{
    const size_t SZ = 256;
    char datestr[SZ] = {'\0'};
    const std::time_t TIME = std::time( nullptr );

    if ( TIME == -1 )
    {
        // This error must not happen
        SDL_LogCritical( SDL_LOG_CATEGORY_ERROR,
                         "Internal error - Cannot get the time" );
        return std::string();
    }

    const struct tm * const TMP = localtime( &TIME );

    if ( TMP == nullptr )
    {
        // This error must not happen
        SDL_LogCritical( SDL_LOG_CATEGORY_ERROR,
                         "Internal error - Cannot get the local time" );
        return std::string();
    }

    std::ostringstream ss;
    std::strftime( datestr, SZ, "[%Y-%m-%d %H:%M:%S.", TMP );
    ss << getMillisTime() << "] ";

    return datestr + ss.str();
}

}   // namespace

namespace lx
{

namespace Log
{
// Debug
bool debug_mode = false;

bool isDebugMode() noexcept
{
    return debug_mode;
}


void setDebugMode( bool debug ) noexcept
{
    if ( debug )
        SDL_LogSetAllPriority( SDL_LOG_PRIORITY_DEBUG );
    else
        setDefaultPriority();

    debug_mode = debug;
}


void setDefaultPriority() noexcept
{
    SDL_LogResetPriorities();
}

void setVerbosePriority( LogType category ) noexcept
{
    SDL_LogSetPriority( category, SDL_LOG_PRIORITY_VERBOSE );
}

void setDebugPriority( LogType category ) noexcept
{
    SDL_LogSetPriority( category, SDL_LOG_PRIORITY_DEBUG );
}

void setInfoPriority( LogType category ) noexcept
{
    SDL_LogSetPriority( category, SDL_LOG_PRIORITY_INFO );
}

void setWarningPriority( LogType category ) noexcept
{
    SDL_LogSetPriority( category, SDL_LOG_PRIORITY_WARN );
}

void setErrorPriority( LogType category ) noexcept
{
    SDL_LogSetPriority( category, SDL_LOG_PRIORITY_ERROR );
}

void setCriticalPriority( LogType category ) noexcept
{
    SDL_LogSetPriority( category, SDL_LOG_PRIORITY_CRITICAL );
}


void logVerbose( LogType category, std::string format, ... ) noexcept
{
    va_list args;
    va_start( args, format );
    std::string str = getDate() + format;
    SDL_LogMessageV( category, SDL_LOG_PRIORITY_VERBOSE, str.c_str(), args );
    va_end( args );
}

void logDebug( LogType category, std::string format, ... ) noexcept
{
    va_list args;
    va_start( args, format );
    std::string str = "   " +  getDate() + format;
    SDL_LogMessageV( category, SDL_LOG_PRIORITY_DEBUG, str.c_str(), args );
    va_end( args );
}

void logInfo( LogType category, std::string format, ... ) noexcept
{
    va_list args;
    va_start( args, format );
    std::string str = "    " + getDate() + format;
    SDL_LogMessageV( category, SDL_LOG_PRIORITY_INFO, str.c_str(), args );
    va_end( args );
}

void logWarning( LogType category, std::string format, ... ) noexcept
{
    va_list args;
    va_start( args, format );
    std::string str = "    " + getDate() + format;
    SDL_LogMessageV( category, SDL_LOG_PRIORITY_WARN, str.c_str(), args );
    va_end( args );
}

void logError( LogType category, std::string format, ... ) noexcept
{
    va_list args;
    va_start( args, format );
    std::string str = "   " + getDate() + format;
    SDL_LogMessageV( category, SDL_LOG_PRIORITY_ERROR, str.c_str(), args );
    va_end( args );
}

void logCritical( LogType category, std::string format, ... ) noexcept
{
    va_list args;
    va_start( args, format );
    std::string str = getDate() + format;
    SDL_LogMessageV( category, SDL_LOG_PRIORITY_CRITICAL, str.c_str(), args );
    va_end( args );
}

void log( std::string format, ... ) noexcept
{
    va_list args;
    va_start( args, format );
    std::string str = "    " + getDate() + format;
    SDL_LogMessageV( APPLICATION, SDL_LOG_PRIORITY_INFO, str.c_str(), args );
    va_end( args );
}

}   // Log

}   // lx
