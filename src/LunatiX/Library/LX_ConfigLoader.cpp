
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

/**
*	@file LX_ConfigLoader.cpp
*	@brief The configuration loader class implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_ConfigLoader.hpp>
#include <LunatiX/LX_Log.hpp>

#include <cstdlib>
#include <fstream>
#include <regex>

namespace
{
    const std::string ONE("1");
    const char SHARP = '#';
};


namespace LX_ConfigLoader
{

void loadSDLfileConfig(LX_InternalConfig& config)
{
    const std::regex VIDEO_REG("video=[[:digit:]]+",std::regex::extended);
    const std::regex VSYNC_REG("vsync=[[:digit:]]+",std::regex::extended);
    const std::regex TTF_REG("ttf=[[:digit:]]+",std::regex::extended);
    const std::regex AUDIO_REG("audio=[[:digit:]]+",std::regex::extended);
    const std::regex GAMEPAD_REG("joystick=[[:digit:]]+",std::regex::extended);
    const std::regex OPENGL_REG("opengl=[[:digit:]]+",std::regex::extended);
    const std::regex FONT_REG("font=.+",std::regex::extended);
    const std::regex SIZE_REG("size=.+",std::regex::extended);

    std::ifstream f;
    f.open(LX_SDL_FILE,std::ios::in);

    if(f.is_open() == false)
    {
        LX_Log::logCritical(LX_Log::LX_LOG_SYSTEM,
                            "loadSDLfileConfig - Cannot open %s",LX_SDL_FILE);
        return;
    }

    int cpt = 0;
    std::string line;

    while(getline(f,line))
    {
        if(line.empty() || line[0] == SHARP)
            continue;

        std::string s = line.substr(line.find("=") + 1);

        switch(cpt)
        {
        case 0:
            if(std::regex_match(line,VIDEO_REG))
            {
                config.video_flag = (s == ONE);
                cpt++;
            }
            break;

        case 1:
            if(std::regex_match(line,VSYNC_REG))
            {
                config.vsync_flag = (s == ONE);
                cpt++;
            }
            break;

        case 2:
            if(std::regex_match(line,TTF_REG))
            {
                config.ttf_flag = (s == ONE);
                cpt++;
            }
            break;

        case 3:
            if(std::regex_match(line,AUDIO_REG))
            {
                config.audio_flag = (s == ONE);
                cpt++;
            }
            break;

        case 4:
            if(std::regex_match(line,GAMEPAD_REG))
            {
                config.gamepad_flag = (s == ONE);
                cpt++;
            }
            break;

        case 5:
            if(std::regex_match(line,OPENGL_REG))
            {
                config.opengl_flag = (s == ONE);
                cpt++;
            }
            break;

        case 6:
            if(std::regex_match(line,FONT_REG))
            {
                config.font_file = s;
                cpt++;
            }
            break;

        case 7:
            if(std::regex_match(line,SIZE_REG))
            {
                config.font_size = atoi(s.c_str());
                cpt++;
            }
            break;

        default:
            break;
        }
    }

    f.close();
}

void loadWindowFileConfig(LX_InternalConfig& config)
{
    const std::regex WIDTH_REG("width=.+",std::regex::extended);
    const std::regex HEIGHT_REG("height=.+",std::regex::extended);
    const std::regex FULLSCREEN_REG("fullscreen=[[:digit:]]+",std::regex::extended);

    std::ifstream f;
    f.open(LX_WINFO_FILE,std::ios::in);

    if(f.is_open() == false)
    {
        LX_Log::logCritical(LX_Log::LX_LOG_SYSTEM,
                            "loadWindowFileConfig - Cannot open %s",
                            LX_SDL_FILE);
        return;
    }

    int cpt = 0;
    std::string line;

    while(getline(f,line))
    {
        if(line.empty() || line[0] == SHARP)
            continue;

        std::string s = line.substr(line.find("=") + 1);

        switch(cpt)
        {
        case 0:
            if(std::regex_match(line,WIDTH_REG))
            {
                config.width = atoi(s.c_str());
                cpt++;
            }
            break;

        case 1:
            if(std::regex_match(line,HEIGHT_REG))
            {
                config.height = atoi(s.c_str());
                cpt++;
            }
            break;

        case 2:
            if(std::regex_match(line,FULLSCREEN_REG))
            {
                config.fullscreen_flag = (s == ONE);
                cpt++;
            }
            break;

        default:
            break;
        }
    }

    f.close();
}

};
