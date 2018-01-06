
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

template <class LX_Fun, class... LX_Args >
LX_Thread::LX_Thread(bool detach, LX_Fun&& fun, LX_Args&&... args)
    : thread(fun, args...)
{
    if(detach)
        thread.detach();
}
