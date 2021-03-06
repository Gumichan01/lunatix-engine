
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

#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

/**
*   @file Time.hpp
*   @brief The timer interface
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <cstdint>

/**
*   @ingroup System
*   @namespace lx::Time
*   @brief Very simple namespace for handling time
*
*   LunatiX has a global timer, based on SDL timer. This timer is launched at the library
*   initialization. It is possible to the elapsed time since LunatiX has been
*   initialized by calling ::getTicks().
*
*   It is also possible to use a local timer (see Timer). It can be used as a stopwatch
*   for specific needs.
*
*   @note Every measures are in millisecond (ms)
*
*/
namespace lx
{

namespace Time
{
/**
*   @fn uint32_t getTicks()
*   Get the elapsed time since the initialization of the Library (ms)
*   @return 32-bit unsinged value
*/
uint32_t getTicks() noexcept;
/**
*   @fn void delay(uint32_t ms)
*   Wait for a certain number of milliseconds before returning
*   @param [in] ms The delay, in millisecond (ms)
*/
void delay( uint32_t ms ) noexcept;

/**
*   @fn uint32_t seconds( uint32_t ms ) noexcept
*   Conversion, millisecond to second
*
*   @param [in] ms value in millisecond (ms)
*   @return The value in second
*/
uint32_t seconds( uint32_t ms ) noexcept;
/**
*   @fn uint32_t minutes( uint32_t ms ) noexcept
*   Conversion, millisecond to minute
*
*   @param [in] ms value in millisecond (ms)
*   @return The value in minute
*/
uint32_t minutes( uint32_t ms ) noexcept;
/**
*   @fn uint32_t hours( uint32_t ms ) noexcept
*   Conversion, millisecond to hour
*
*   @param [in] ms value to convert
*   @return The value in hour
*/
uint32_t hours( uint32_t ms ) noexcept;


/**
*   @class Timer
*   @brief The chronograph/stopwatch
*/
class Timer final
{
    uint32_t m_start = 0U;
    uint32_t m_pause = 0U;
    uint32_t m_tradeoff = 0U;
    bool m_stopped = true;
    bool m_paused  = false;

public:

    Timer() = default;

    /**
    *   @fn void start() noexcept
    *   Start the timer
    *
    *   @note This function has no effect if the timer has already been started
    *
    *   @sa isStopped
    *   @sa isPaused
    */
    void start() noexcept;
    /**
    *   @fn void pause() noexcept
    *   Pause the timer
    *
    *   @note This function has no effect if the timer is in pause or has been stopped
    */
    void pause() noexcept;
    /**
    *   @fn void resume() noexcept
    *   Resume the timer that has been paused
    *
    *   @note This function has no effect if the timer has been stopped
    */
    void resume() noexcept;
    /**
    *   @fn uint32_t lap() noexcept
    *   Return the time in a lap and restart the timer
    *
    *   @return the current time since the timer started, in millisecond (ms)
    *
    *   @note This behaviour is equivalent to this piece of code:
    *   ```
    *   uint32_t t = getTicks();
    *   stop();
    *   reset();
    *   start();
    *   ```
    */
    uint32_t lap() noexcept;
    /**
    *   @fn void stop() noexcept
    *   Stop the timer
    *
    *   @note This function has no effect if the timer has already been stopped
    */
    void stop() noexcept;
    /**
    *   @fn void reset() noexcept
    *   Reset the timer.
    *   This operation can be done even if the timer is still running.
    *
    *   @note It is strongly recommended to stop() or pause() the timer before resetting
    *   the timer
    */
    void reset() noexcept;
    /**
    *   @fn uint32_t getTicks() noexcept
    *   Return the time.
    *
    *   @return The current time since the timer started, in millisecond (ms)
    *
    *   @note This function can be called at any moment.
    */
    uint32_t getTicks() noexcept;
    /**
    *   @fn bool isStopped() noexcept
    *   Check if the timer is stopped
    *
    *   @return boolean
    */
    bool isStopped() noexcept;
    /**
    *   @fn bool isPaused() noexcept
    *   Check if the timer is paused
    *
    *   @return boolean
    */
    bool isPaused() noexcept;
    ~Timer() = default;
};

}   //Time

}   // lx

#endif // TIMER_HPP_INCLUDED
