
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

#ifndef LX_FORMAT_H_INCLUDED
#define LX_FORMAT_H_INCLUDED

#include <SDL2/SDL_pixels.h>


namespace LX_Graphics
{

enum class LX_PIXELFORMAT : uint32_t
{
    UNKNOWN     = SDL_PIXELFORMAT_UNKNOWN,
    INDEX1LSB   = SDL_PIXELFORMAT_INDEX1LSB,
    INDEX1MSB   = SDL_PIXELFORMAT_INDEX1MSB,
    INDEX4LSB   = SDL_PIXELFORMAT_INDEX4LSB,
    INDEX4MSB   = SDL_PIXELFORMAT_INDEX4MSB,
    INDEX8      = SDL_PIXELFORMAT_INDEX8,
    RGB332      = SDL_PIXELFORMAT_RGB332,
    RGB444      = SDL_PIXELFORMAT_RGB444,
    RGB555      = SDL_PIXELFORMAT_RGB555,
    BGR555      = SDL_PIXELFORMAT_BGR555,
    ARGB4444    = SDL_PIXELFORMAT_ARGB4444,
    RGBA4444    = SDL_PIXELFORMAT_RGBA4444,
    ABGR4444    = SDL_PIXELFORMAT_ABGR4444,
    BGRA4444    = SDL_PIXELFORMAT_BGRA4444,
    ARGB1555    = SDL_PIXELFORMAT_ARGB1555,
    RGBA5551    = SDL_PIXELFORMAT_RGBA5551,
    ABGR1555    = SDL_PIXELFORMAT_ABGR1555,
    BGRA5551    = SDL_PIXELFORMAT_BGRA5551,
    RGB565      = SDL_PIXELFORMAT_RGB565,
    BGR565      = SDL_PIXELFORMAT_BGR565,
    RGB24       = SDL_PIXELFORMAT_RGB24,
    BGR24       = SDL_PIXELFORMAT_BGR24,
    RGB888      = SDL_PIXELFORMAT_RGB888,
    RGBX8888    = SDL_PIXELFORMAT_RGBX8888,
    BGR888      = SDL_PIXELFORMAT_BGR888,
    BGRX8888    = SDL_PIXELFORMAT_BGRX8888,
    ARGB8888    = SDL_PIXELFORMAT_ARGB8888,
    RGBA8888    = SDL_PIXELFORMAT_RGBA8888,
    ABGR8888    = SDL_PIXELFORMAT_ABGR8888,
    BGRA8888    = SDL_PIXELFORMAT_BGRA8888,
    ARGB2101010 = SDL_PIXELFORMAT_ARGB2101010,
    YV12        = SDL_PIXELFORMAT_YV12,
    IYUV        = SDL_PIXELFORMAT_IYUV,
    YUY2        = SDL_PIXELFORMAT_YUY2,
    UYVY        = SDL_PIXELFORMAT_UYVY,
    YVYU        = SDL_PIXELFORMAT_YVYU
};

}

#endif  // LX_IMAGE_H_INCLUDED
