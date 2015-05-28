

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Particle.cpp
*	@brief The particle implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include "LX_Particle.hpp"
#include "LX_Physics.hpp"
#include "LX_Graphics.hpp"

using namespace LX_Graphics;

LX_Particle::LX_Particle(const int x , const int y, const int w, const int h)
{
    init(x,y,w,h,0,0);
}


LX_Particle::LX_Particle(const LX_AABB *b)
{
    init(b->x,b->y,b->w,b->h,0,0);
}


LX_Particle::LX_Particle(const int x , const int y, const int w, const int h,
                            const LX_Vector2D *v)
{
    init(x,y,w,h,v->vx,v->vy);
}



LX_Particle::LX_Particle(const int x , const int y, const int w,
                const int h, const int vx , const int vy)
{
    init(x,y,w,h,vx,vy);
}


LX_Particle::LX_Particle(const LX_AABB *b, const int vx , const int vy)
{
    init(b->x,b->y,b->w,b->h,vx,vy);
}



LX_Particle::LX_Particle(const LX_AABB *b, const LX_Vector2D *v)
{
    init(b->x,b->y,b->w,b->h,v->vx,v->vy);
}


void LX_Particle::init(const int x , const int y, const int w,
                        const int h, const int vx, const int vy)
{
    box = {x,y,w,h};
    velocity = {vx,vy};

    lifetime = 16;

    texture = NULL;
    surface = NULL;
}



LX_Particle::~LX_Particle()
{
    if(surface != NULL)
    {
        SDL_FreeSurface(surface);
    }

    if(surface != NULL)
    {
        SDL_DestroyTexture(texture);
    }
}



void LX_Particle::update(void)
{
    if(lifetime > 0)
    {
        LX_Physics::moveRect(&box,velocity.vx,velocity.vy);
        lifetime--;
    }
}


bool LX_Particle::isDead(void)
{
    return lifetime == 0;
}


bool LX_Particle::setTexture(const char * str, const unsigned int id)
{
    texture = loadTextureFromFile(str,id);

    return texture != NULL;
}


bool LX_Particle::setSurface(const char * str)
{
    surface = loadSurface(str);

    return surface != NULL;
}


void LX_Particle::setSpeed(int x,int y)
{
    velocity = {x, y};
}


SDL_Texture * LX_Particle::getTexture(void)
{
    return texture;
}



SDL_Surface * LX_Particle::getSurface(void)
{
    return surface;
}


LX_AABB * LX_Particle::getAABB()
{
    return &box;
}


const int LX_Particle::getX(void)
{
    return box.x;
}



const int LX_Particle::getY(void)
{
    return box.y;
}



const int LX_Particle::getW(void)
{
    return box.w;
}



const int LX_Particle::getH(void)
{
    return box.h;
}

