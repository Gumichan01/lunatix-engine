
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

#ifndef LX_VERSION_HPP_INCLUDED
#define LX_VERSION_HPP_INCLUDED

/**
*   @file LX_Version.hpp
*   @brief The version library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <string>

/**
*   @ingroup Config
*   @namespace LX_VersionInfo
*   @brief Information about the library
*/
namespace LX_VersionInfo
{

/**
*   @struct LX_Version
*   @brief The version structure
*   The current version of the library
*/
struct LX_Version
{
    short major;        /**< Major version  */
    short minor;        /**< Minor version  */
    short patch;        /**< Patch version  */
    std::string status; /**< Status         */
};

/**
*   @fn void info() noexcept
*   Get information about the library
*/
void info() noexcept;

/**
*   @fn void getVersion(LX_Version& version) noexcept
*   Get the version of the library
*   @param [out] version The structure to fill in.
*/
void getVersion(LX_Version& version) noexcept;

/**
*   @fn void dependencies() noexcept
*   Display information about the library and its dependencies
*/
void dependencies() noexcept;

}

#endif // LX_VERSION_HPP_INCLUDED
