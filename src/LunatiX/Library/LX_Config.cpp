
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
*	@file LX_Config.cpp
*	@brief The configuration class implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <cstring>
#include <exception>
#include <sstream>

#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Error.hpp>


// unique instance
static LX_Configuration *instance = nullptr;


LX_ConfigurationException::LX_ConfigurationException(UTF8string err)
{
    _string_error = err;
}

const char * LX_ConfigurationException::what() const noexcept
{
    return _string_error.utf8_str();
}

LX_ConfigurationException::~LX_ConfigurationException() noexcept {}


/*
*
*   Create an instance of the configuration
*
*/
LX_Configuration::LX_Configuration()
{
    // Load configuration
    loadSDLFlags_();
}

LX_Configuration::~LX_Configuration() {}

void LX_Configuration::initConfig()
{
    if(instance == nullptr)
    {
        try
        {
            instance = new LX_Configuration();
        }
        catch(std::exception & ex_conf)
        {
            LX_SetError(ex_conf.what());
            instance = nullptr;
        }
    }
}

LX_Configuration * LX_Configuration::getInstance()
{
    return instance;
}

void LX_Configuration::destroy()
{
    delete instance;
    instance = nullptr;
}

void LX_Configuration::loadSDLFlags_()
{
    LX_ConfigLoader::loadSDLfileConfig(_conf);
    LX_ConfigLoader::loadWindowFileConfig(_conf);
}

bool LX_Configuration::getVideoFlag()
{
    return _conf.video_flag;
}

bool LX_Configuration::getVSyncFlag()
{
    return _conf.vsync_flag;
}

bool LX_Configuration::getTTFFlag()
{
    return _conf.ttf_flag;
}

bool LX_Configuration::getAudioFlag()
{
    return _conf.audio_flag;
}

bool LX_Configuration::getGamepadFlag()
{
    return _conf.gamepad_flag;
}

bool LX_Configuration::getOpenGLFlag()
{
    return _conf.opengl_flag;
}

const char * LX_Configuration::getFontFile()
{
    return _conf.font_file.utf8_str();
}

int LX_Configuration::getFontSize()
{
    return _conf.font_size;
}

int LX_Configuration::getWinWidth()
{
    return _conf.width;
}

int LX_Configuration::getWinHeight()
{
    return _conf.height;
}

bool LX_Configuration::getFullscreenFlag()
{
    return _conf.fullscreen_flag;
}
