
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

template <class Fun, class... Args >
Thread::Thread(bool detach, Fun&& fun, Args&&... args)
    : _thread(fun, args...)
{
    if(detach)
        _thread.detach();
}

template <class ReturnValue>
template <class Fun, class... Args>
ASyncTask<ReturnValue>::ASyncTask(Fun&& fun, Args&&... args)
    : _future(std::async(std::launch::async, fun, args...)) {}

template <class ReturnValue>
ReturnValue ASyncTask<ReturnValue>::getResult()
{
    return _future.get();
}
