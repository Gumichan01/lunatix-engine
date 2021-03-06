
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

#ifndef RANDOM_HPP_INCLUDED
#define RANDOM_HPP_INCLUDED

/**
*   @file Random.hpp
*   @brief The Random Number Generator library
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <type_traits>
#include <limits>

namespace lx
{

/**
*   @ingroup System
*   @namespace lx::Random
*   @brief The Random Number Generator (RNG) namespace
*
*   This random number generator can be used using the Xorshift* generator,
*   or the standard C generator.
*/
namespace Random
{

/**
*   @fn void initRand() noexcept
*   Initializes the random number generator
*   setting a seed
*/
void initRand() noexcept;

/**
*   @typedef template <typename N> Num
*   @brief Statically define a positive Number
*   @param Num
*/
template <typename N>
using Num =
    typename std::enable_if < std::is_integral< N >::value &&
    std::is_unsigned< N >::value &&
    !std::is_same< N, bool >::value &&
    !std::is_same< N, unsigned char >::value, N >::type;

/**
*   @fn template <typename T> Num<T> xrand(T min = 0, T max = std::numeric_limits<T>::max()) noexcept
*   Returns a pseudorandom number between min and max
*
*   @param min
*   @param max
*
*   @return An integer value between min and max
*
*   @pre min >= 0 ∧ min < max
*
*   @note This function uses the Xorshift* Random Number generator
*/
template <typename T>
Num<T> xrand( T min = 0U, T max = std::numeric_limits< T >::max() ) noexcept;


/**
*   @fn float fxrand(float minf = 0.0f, float maxf = 1.0f) noexcept
*   Returns a pseudorandom number between min andf maxf
*
*   @param minf
*   @param maxf
*
*   @return An integer value between minf and maxf
*
*   @pre minf >= 0.0f ∧ minf < maxf
*
*   @note This function uses the Xorshift* Random Number generator
*/
float fxrand( float minf = 0.0f, float maxf = 1.0f ) noexcept;

#include "Random.tpp"

}   // Random

}   // lx

#endif // RANDOM_HPP_INCLUDED
