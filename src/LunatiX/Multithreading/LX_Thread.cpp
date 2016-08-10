
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

#include <LunatiX/LX_Thread.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_Log.hpp>
#include <SDL2/SDL_thread.h>

#include <functional>
#include <stdexcept>


namespace
{

using LX_ThreadFun_ = int(void *);

class LX_Thread_
{
    std::function<LX_ThreadFun_> _f;
    std::string _name;
    bool _joinable;
    SDL_Thread * _thread;
    LX_Multithreading::LX_Data _data;

public:

    LX_Thread_(const std::function<LX_ThreadFun_>& f, std::string name,
               LX_Multithreading::LX_Data data)
        : _f(f), _name(name), _joinable(true), _thread(nullptr), _data(data) {}


    void start()
    {
        _thread = SDL_CreateThread(*_f.target<LX_ThreadFun_>(),_name.c_str(),_data);

        if(_thread == nullptr)
        {
            LX_Log::logCritical(LX_Log::LX_LOG_APPLICATION,"Couldn't launch the thread: %d",LX_GetError());
            throw std::runtime_error("An error occurred while starting the thread");
        }
    }

    bool joinable()        // TRUE si ni detach() ni join() a été appelé
    {
        return _joinable;
    }

    void join(int& ret)            // invalid_argument if the thread is not joinable
    {
        if(!_joinable)
        {
            LX_Log::logCritical(LX_Log::LX_LOG_APPLICATION,
                                "Thread %s #%ld: not joinable",
                                SDL_GetThreadName(_thread),getID());
            throw std::invalid_argument("This thread is detached or has already been joined");
        }

        SDL_WaitThread(_thread,&ret);
        _joinable = false;
    }

    void detach()
    {
        if(!_joinable)
        {
            LX_Log::logCritical(LX_Log::LX_LOG_APPLICATION,
                                "Thread %s #%ld: cannot be detached",
                                SDL_GetThreadName(_thread),getID());
            throw std::invalid_argument("This thread is already detached or has been joined");
        }

        SDL_DetachThread(_thread);
        _joinable = false;
    }

    unsigned long getID() const
    {
        return SDL_GetThreadID(_thread);
    }
    std::string getName() const
    {
        return SDL_GetThreadName(_thread);
    }

    ~LX_Thread_();
};

};




namespace LX_Multithreading
{



};
