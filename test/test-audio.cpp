

#include <LunatiX/Lunatix_engine.hpp>
#include <iostream>
#include <string>

void test_audioInit();
void test_music();
void test_chunk();
void test_fx();
void test_volume();


int main(int argc, char **argv)
{
    bool err = LX_Init();

    if(!err)
        std::cerr << "FAILURE - Init does not work" << std::endl;
    else
        std::cout << "SUCCESS - LunatiX Engine have been initialized with success"
                  << std::endl;

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Audio ==== ");
    test_audioInit();
    test_music();
    LX_Log::log(" ==== End Audio ==== ");

    return EXIT_SUCCESS;
}


void test_audioInit()
{
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION," = TEST audio = ");

    int n, freq, channels;
    Uint16 format;
    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"Get information about the library");
    n = Mix_QuerySpec(&freq, &format, &channels);

    if(n == 0)
    {
        LX_Log::logError(LX_Log::LX_LOG_TEST,"Cannot get information: %s",
                        Mix_GetError());
    }
    else
    {
        std::string format_str = "Unknown";

        switch(format)
        {
            case AUDIO_U8: format_str="U8"; break;
            case AUDIO_S8: format_str="S8"; break;
            case AUDIO_U16LSB: format_str="U16LSB"; break;
            case AUDIO_S16LSB: format_str="S16LSB"; break;
            case AUDIO_U16MSB: format_str="U16MSB"; break;
            case AUDIO_S16MSB: format_str="S16MSB"; break;
            default: break;
        }
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"opened = %d time(s)",n);
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"frequency = %d Hz",freq);
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"format = %s",format_str.c_str());
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"channels = %d",channels);

        int m = Mix_GetNumChunkDecoders();

        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"Get the chunk decoders");
        for(int i = 0; i < m; i++)
        {
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"Sample chunk decoder %d: %s",
                            i,Mix_GetChunkDecoder(i));
        }

        m = Mix_GetNumMusicDecoders();

        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"Get the music decoders");
        for(int j = 0; j < m; j++)
        {
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"Sample chunk decoder %d: %s",
                            j,Mix_GetMusicDecoder(j));
        }
    }

    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION," = END TEST = ");
}

void test_music()
{
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION," = TEST music = ");
    std::string s = "data/01.ogg";
    LX_Mixer::LX_Music *music = nullptr;

    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"Launch music: %s",s.c_str());

    try
    {
        music = LX_Mixer::loadMusic(s);
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - music launched");
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"play music");

        if(music->play())
        {
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - play music OK");
            SDL_Delay(4000);
            music->pause();
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"music paused during 1 second");
            SDL_Delay(1000);
            music->pause();
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"music resumed");
            SDL_Delay(2000);
            music->stop();
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"music stopped");

        }
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - play music KO");

        delete music;
    }
    catch(LX_Mixer::LX_MusicException& e)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Cannot launch the music: %s",e.what());
    }

    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"Launch music: <empty_string>");

    try
    {
        music = LX_Mixer::loadMusic("");
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - music launched, it should not");
        delete music;
    }
    catch(...)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - failure exception expected");
    }

    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION," = END TEST = ");
}
