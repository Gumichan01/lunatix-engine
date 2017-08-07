
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file LX_Texture.cpp
*   @brief The implementation of the image
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*
*/

#include <LunatiX/LX_Texture.hpp>
#include <LunatiX/LX_TrueTypeFont.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Error.hpp>

#include <SDL2/SDL_image.h>

#define RENDER(x) static_cast<SDL_Renderer*>(x)

namespace
{

const LX_AABB rnull = {0,0,0,0};
const LX_Colour cnull = {0,0,0,0};

SDL_RendererFlip shortToFlip_(const short mirror)
{
    if(mirror == 1)
        return SDL_FLIP_HORIZONTAL;
    else if(mirror == 2)
        return SDL_FLIP_VERTICAL;

    return SDL_FLIP_NONE;
}

double radianToDegree(const double angle)
{
    return angle * 180 / M_PI;
}

// Load a image from a file
SDL_Surface * loadSurface_(const std::string& filename, uint32_t format)
{
    SDL_Surface *loaded = IMG_Load(filename.c_str());

    if(loaded == nullptr)
        return nullptr;

    SDL_Surface *optimized = SDL_ConvertSurfaceFormat(loaded,format,0);
    SDL_FreeSurface(loaded);
    return optimized;
}

// Load a texture from a file
SDL_Texture * loadTexture_(const std::string& filename,
                           uint32_t format, SDL_Renderer *r)
{
    SDL_Surface *tmp_s = loadSurface_(filename, format);

    if(tmp_s == nullptr)
        return nullptr;

    SDL_Texture *tmp_t = SDL_CreateTextureFromSurface(r,tmp_s);
    SDL_FreeSurface(tmp_s);
    return tmp_t;
}

}

namespace LX_Graphics
{

LX_ImageException::LX_ImageException(std::string err) : _string_error(err) {}

LX_ImageException::LX_ImageException(const LX_ImageException& me)
    : _string_error(me._string_error) {}

const char * LX_ImageException::what() const noexcept
{
    return _string_error.c_str();
}


/** LX_Texture */

//  protected zero-argument constructor
LX_Texture::LX_Texture(LX_Win::LX_Window& w, uint32_t format)
    : _texture(nullptr), _win(w), _format(format) {}


LX_Texture::LX_Texture(SDL_Texture *t, LX_Win::LX_Window& w, uint32_t format)
    : _texture(t), _win(w), _format(format) {}


LX_Texture::LX_Texture(const std::string& filename, LX_Win::LX_Window& w,
                       uint32_t format)
    : _texture(nullptr), _win(w), _format(format)
{
    _texture = loadTexture_(filename, format, RENDER(w.getRenderingSys()));

    if(_texture == nullptr)
        throw LX_ImageException("LX_Texture — Cannot load " + filename);
}


LX_Texture::LX_Texture(const UTF8string& filename, LX_Win::LX_Window& w,
                       uint32_t format)
    : LX_Texture(filename.utf8_str(),w,format) {}


void LX_Texture::draw()
{
    SDL_RenderCopy(RENDER(_win.getRenderingSys()),_texture,nullptr,nullptr);
}


bool LX_Texture::bind(float *iw, float *ih)
{
    return _win.glMakeCurrent() && SDL_GL_BindTexture(_texture,iw,ih) == 0;
}

bool LX_Texture::unbind()
{
    return SDL_GL_UnbindTexture(_texture) == 0;
}


LX_Win::LX_Window& LX_Texture::getWindow() const
{
    return _win;
}

uint32_t LX_Texture::getFormat() const
{
    return _format;
}


LX_Texture::~LX_Texture()
{
    if(_texture != nullptr) SDL_DestroyTexture(_texture);
}


/** LX_Sprite */

// protected constructor
LX_Sprite::LX_Sprite(SDL_Texture *t, LX_Win::LX_Window& w,
                     LX_AABB * sprite_area, uint32_t format)
    : LX_Texture(t,w,format), _sprite_area(nullptr)
{
    setSpriteArea(sprite_area);
}


LX_Sprite::LX_Sprite(const std::string& filename, LX_Win::LX_Window& w,
                     uint32_t format)
    : LX_Sprite(filename,w,nullptr,format) {}

LX_Sprite::LX_Sprite(const std::string& filename, LX_Win::LX_Window& w,
                     LX_AABB * sprite_area, uint32_t format)
    : LX_Texture(filename,w,format), _sprite_area(nullptr)
{
    setSpriteArea(sprite_area);
}


LX_Sprite::LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
                     uint32_t format)
    : LX_Sprite(filename,w,nullptr,format) {}


LX_Sprite::LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
                     LX_AABB * sprite_area, uint32_t format)
    : LX_Texture(filename,w,format), _sprite_area(nullptr)
{
    setSpriteArea(sprite_area);
}


void LX_Sprite::setSpriteArea(LX_AABB * sprite_area)
{
    if(sprite_area != nullptr)
    {
        _sprite_area = new LX_AABB();
        *_sprite_area = *sprite_area;
    }
}


void LX_Sprite::draw()
{
    LX_Texture::draw();
}

void LX_Sprite::draw(LX_AABB * box)
{
    draw(box,0.0);
}


void LX_Sprite::draw(LX_AABB * box, const double angle)
{
    draw(box,angle,LX_MIRROR_NONE);
}

void LX_Sprite::draw(LX_AABB * box, const double angle, const short mirror)
{
    SDL_RenderCopyEx(RENDER(_win.getRenderingSys()),_texture,_sprite_area,box,
                     (-radianToDegree(angle)),nullptr,shortToFlip_(mirror));
}

LX_Sprite::~LX_Sprite()
{
    delete _sprite_area;
}


/** LX_AnimatedSprite */

// protected constructor
LX_AnimatedSprite::LX_AnimatedSprite(SDL_Texture *t, LX_Win::LX_Window& w,
                                     const std::vector<LX_AABB>& coord,
                                     const uint32_t delay, bool loop,
                                     uint32_t format)
    : LX_Sprite(t,w,nullptr,format), _coordinates(coord), _SZ(coord.size()),
      _delay(delay), _btime(0), _frame(0), _started(false), _loop(loop), _drawable(true) {}


LX_AnimatedSprite::LX_AnimatedSprite(const std::string& filename,
                                     LX_Win::LX_Window& w,
                                     const std::vector<LX_AABB>& coord,
                                     const uint32_t delay, bool loop,
                                     uint32_t format)
    : LX_AnimatedSprite(UTF8string(filename), w, coord, delay, loop, format) {}


LX_AnimatedSprite::LX_AnimatedSprite(const UTF8string& filename, LX_Win::LX_Window& w,
                                     const std::vector<LX_AABB>& coord,
                                     const uint32_t delay, bool loop,
                                     uint32_t format)
    : LX_Sprite(filename,w,nullptr,format), _coordinates(coord),
      _SZ(coord.size()), _delay(delay), _btime(0), _frame(0),
      _started(false), _loop(loop), _drawable(true) {}


void LX_AnimatedSprite::draw(LX_AABB * box)
{
    draw(box, 0.0);
}

void LX_AnimatedSprite::draw(LX_AABB * box, const double angle)
{
    draw(box, angle, LX_MIRROR_NONE);
}


void LX_AnimatedSprite::draw(LX_AABB * box, const double angle, const short mirror)
{
    if(!_started)
    {
        _started = true;
        _btime = SDL_GetTicks();
    }
    else if(SDL_GetTicks() - _btime > _delay)
    {
        _btime = SDL_GetTicks();

        if(_frame == _SZ - 1)
        {
            if(_loop)
                _frame = 0;
            else
                _drawable = false;
        }
        else
            _frame += 1;
    }

    if(_drawable)
    {
        SDL_RenderCopyEx(RENDER(_win.getRenderingSys()), _texture,
                         &_coordinates[_frame], box, (-radianToDegree(angle)),
                         nullptr, shortToFlip_(mirror));
    }
}


void LX_AnimatedSprite::resetAnimation()
{
    _started = false;
    _drawable = true;
    _frame = 0;
}


uint32_t LX_AnimatedSprite::getFrameDelay() const
{
    return _delay;
}

bool LX_AnimatedSprite::isInfinitelyLooped() const
{
    return _loop;
}


/** LX_BufferedImage */

LX_BufferedImage::LX_BufferedImage(const std::string& filename, uint32_t format)
{
    _surface = loadSurface_(filename, format);

    if(_surface == nullptr)
        throw LX_ImageException("LX_BufferedImage — Cannot load " + filename);
}


LX_BufferedImage::LX_BufferedImage(const UTF8string& filename, uint32_t format)
    : LX_BufferedImage(filename.utf8_str(),format) {}


LX_BufferedImage::LX_BufferedImage(SDL_Surface * s, uint32_t format)
    : _surface(nullptr)
{
    if(s->format->format != format)
    {
        _surface = SDL_ConvertSurfaceFormat(s,format,0);
        SDL_FreeSurface(s);
    }
}


LX_Texture * LX_BufferedImage::generateTexture(LX_Win::LX_Window& w) const
{
    return new LX_Texture(SDL_CreateTextureFromSurface(RENDER(w.getRenderingSys()),
                          _surface),w);
}

LX_Sprite * LX_BufferedImage::generateSprite(LX_Win::LX_Window& w,
        LX_AABB * sprite_area) const
{
    return new LX_Sprite(SDL_CreateTextureFromSurface(RENDER(w.getRenderingSys()), _surface),
                         w, sprite_area);
}

LX_AnimatedSprite * LX_BufferedImage::
generateAnimatedSprite(LX_Win::LX_Window& w, const std::vector<LX_AABB>& coord,
                       const uint32_t delay, bool loop) const
{
    return new LX_AnimatedSprite(SDL_CreateTextureFromSurface(RENDER(w.getRenderingSys()),_surface),
                                 w, coord, delay, loop);
}


LX_BufferedImage::~LX_BufferedImage()
{
    SDL_FreeSurface(_surface);
}



/** LX_StreamingTexture */

LX_StreamingTexture::LX_StreamingTexture(LX_Win::LX_Window& w, uint32_t format)
    : LX_Texture(w,format), _screen(nullptr), _update(false)
{
    int bpp, width, height;
    uint32_t r,g,b,a;

    if(SDL_PixelFormatEnumToMasks(_format,&bpp,&r,&g,&b,&a) != SDL_TRUE)
    {
        SDL_PixelFormatEnumToMasks(SDL_PIXELFORMAT_RGBA8888,&bpp,&r,&g,&b,&a);
        _format = LX_PIXELFORMAT_RGBA8888;
    }

    LX_Win::LX_WindowInfo info;
    _win.getInfo(info);

    if(info.lw == 0 && info.lh == 0)
    {
        width  = _win.getWidth();
        height = _win.getHeight();
    }
    else
    {
        width  = info.lw;
        height = info.lh;
    }

    if(width <= 0 || height <= 0)
        throw LX_ImageException("LX_StreamingTexture - bad dimensions");
    else
    {
        _screen  = SDL_CreateRGBSurface(0,width,height,bpp,r,g,b,a);
        _texture = SDL_CreateTexture(RENDER(w.getRenderingSys()),_format,
                                     SDL_TEXTUREACCESS_STREAMING,width,height);
    }
}


bool LX_StreamingTexture::blit(LX_BufferedImage& s, LX_AABB& rect)
{
    bool b = (SDL_BlitScaled(s._surface,nullptr,_screen,&rect) == 0);

    if(!_update)
        _update = b;

    return b;
}

void LX_StreamingTexture::update()
{
    if(_update)
    {
        SDL_UpdateTexture(_texture,nullptr,_screen->pixels,_screen->pitch);
        SDL_FillRect(_screen,nullptr,SDL_MapRGBA(_screen->format,0,0,0,0));
        _update = false;
    }
}


LX_StreamingTexture::~LX_StreamingTexture()
{
    SDL_FreeSurface(_screen);
}



/** LX_TextTexture */

LX_TextTexture::LX_TextTexture(LX_TrueTypeFont::LX_Font& font,
                               LX_Win::LX_Window& w, uint32_t format)
    : LX_Texture(w,format), _text(""), _font(font), _size(0), _colour(cnull),
    _dimension(rnull)
{
    _colour = _font.getColour_();
    _size = _font.getSize_();
}


LX_TextTexture::LX_TextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                               LX_Win::LX_Window& w, uint32_t format)
    : LX_TextTexture(UTF8string(text), font.getSize_(), font, w, format) {}

LX_TextTexture::LX_TextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                               LX_Win::LX_Window& w, uint32_t format)
    : LX_TextTexture(text, font.getSize_(), font, w, format) {}


LX_TextTexture::LX_TextTexture(const std::string& text, unsigned int sz,
                               LX_TrueTypeFont::LX_Font& font,
                               LX_Win::LX_Window& w, uint32_t format)
    : LX_TextTexture(UTF8string(text), sz, font, w, format) {}


LX_TextTexture::LX_TextTexture(const UTF8string& text, unsigned int sz,
                               LX_TrueTypeFont::LX_Font& font,
                               LX_Win::LX_Window& w, uint32_t format)
    : LX_Texture(w,format), _text(text), _font(font), _size(sz),
      _colour(_font.getColour_()), _dimension(rnull)
{
    _font.sizeOfText_(_text,_size,_dimension.w,_dimension.h);
}


void LX_TextTexture::draw()
{
    draw(0.0);
}


void LX_TextTexture::draw(const double angle)
{
    draw(angle,LX_MIRROR_NONE);
}


void LX_TextTexture::draw(const double angle, const short mirror)
{
    SDL_RenderCopyEx(RENDER(_win.getRenderingSys()),_texture,nullptr,
                     &_dimension, (-radianToDegree(angle)),nullptr,
                     shortToFlip_(mirror));
}

const UTF8string LX_TextTexture::getText() const
{
    return _text;
}

unsigned int LX_TextTexture::getTextSize() const
{
    return _size;
}

void LX_TextTexture::getTextDimension(int& w, int& h)
{
    w = _dimension.w;
    h = _dimension.h;
}

int LX_TextTexture::getTextWidth()
{
    return _dimension.w;
}

int LX_TextTexture::getTextHeight()
{
    return _dimension.h;
}

LX_Colour LX_TextTexture::getTextColour() const
{
    return _colour;
}

void LX_TextTexture::setText(const std::string& text)
{
    setText(text, _size);
}

void LX_TextTexture::setText(const UTF8string& text)
{
    setText(text, _size);
}


void LX_TextTexture::setText(const std::string& text, unsigned int sz)
{
    setText(UTF8string(text),sz);
}


void LX_TextTexture::setText(const UTF8string& text, unsigned int sz)
{
    if(text != _text || _size != sz)
    {
        _text = text;
        _size = sz;
        updateTexture_();
    }
}


void LX_TextTexture::setPosition(int x, int y)
{
    _dimension.x = x;
    _dimension.y = y;
}


void LX_TextTexture::setTextSize(unsigned int sz)
{
    if(_size != sz)
    {
        _size = sz;
        if(!_text.utf8_empty()) updateTexture_();
    }
}


void LX_TextTexture::setTextColour(const LX_Colour& c)
{
    if(_colour != c)
    {
        _colour = c;
        if(!_text.utf8_empty()) updateTexture_();
    }
}


LX_TextTexture::~LX_TextTexture() {}



/** LX_SolidTextTexture */

LX_SolidTextTexture::
LX_SolidTextTexture(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                    uint32_t format)
    : LX_TextTexture(font,w,format) {}


LX_SolidTextTexture::
LX_SolidTextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                    LX_Win::LX_Window& w, uint32_t format)
    : LX_SolidTextTexture(UTF8string(text), font, w, format) {}


LX_SolidTextTexture::
LX_SolidTextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                    LX_Win::LX_Window& w, uint32_t format)
    : LX_SolidTextTexture(text, font.getSize_(), font, w, format) {}

LX_SolidTextTexture::
LX_SolidTextTexture(const std::string& text, unsigned int sz,
                    LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                    uint32_t format)
    : LX_SolidTextTexture(UTF8string(text), sz, font, w, format) {}


LX_SolidTextTexture::
LX_SolidTextTexture(const UTF8string& text, unsigned int sz,
                    LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                    uint32_t format)
    : LX_TextTexture(text,sz,font,w,format)
{
    _texture = _font.drawSolidText_(_text,_size,_win);

    if(_texture == nullptr)
        throw LX_ImageException("LX_SolidTextTexture — Cannot create the texture " +
                                  std::string(text.utf8_str()));
}


void LX_SolidTextTexture::updateTexture_()
{
    const LX_Colour tmp = _font.getColour_();

    if(_texture != nullptr) SDL_DestroyTexture(_texture);
    _font.setColour_(_colour);
    _texture = _font.drawSolidText_(_text,_size,_win);
    _font.sizeOfText_(_text,_size,_dimension.w,_dimension.h);
    _font.setColour_(tmp);
}


/** LX_ShadedTextTexture */

LX_ShadedTextTexture::
LX_ShadedTextTexture(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                     uint32_t format)
    : LX_TextTexture(font,w,format), _bgcolour(cnull) {}


LX_ShadedTextTexture::
LX_ShadedTextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                     const LX_Colour& bg, LX_Win::LX_Window& w, uint32_t format)
    : LX_ShadedTextTexture(UTF8string(text), font, bg, w, format) {}

LX_ShadedTextTexture::
LX_ShadedTextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                     const LX_Colour& bg, LX_Win::LX_Window& w, uint32_t format)
    : LX_ShadedTextTexture(text, font.getSize_(), font, bg, w,format) {}


LX_ShadedTextTexture::
LX_ShadedTextTexture(const std::string& text, unsigned int sz,
                     LX_TrueTypeFont::LX_Font& font, const LX_Colour& bg,
                     LX_Win::LX_Window& w, uint32_t format)
    : LX_ShadedTextTexture(UTF8string(text), sz, font, bg, w, format) {}


LX_ShadedTextTexture::
LX_ShadedTextTexture(const UTF8string& text, unsigned int sz,
                     LX_TrueTypeFont::LX_Font& font, const LX_Colour& bg,
                     LX_Win::LX_Window& w, uint32_t format)
    : LX_TextTexture(text,sz,font,w,format), _bgcolour(bg)
{
    _texture = _font.drawShadedText_(_text,_size,_bgcolour,_win);

    if(_texture == nullptr)
        throw LX_ImageException("LX_ShadedTextTexture — Cannot create the texture: " +
                                  std::string(text.utf8_str()));
}


void LX_ShadedTextTexture::updateTexture_()
{
    const LX_Colour tmp = _font.getColour_();

    if(_texture != nullptr) SDL_DestroyTexture(_texture);
    _font.setColour_(_colour);
    _texture = _font.drawShadedText_(_text,_size,_bgcolour,_win);
    _font.sizeOfText_(_text,_size,_dimension.w,_dimension.h);
    _font.setColour_(tmp);
}


void LX_ShadedTextTexture::setBgColour(const LX_Colour& bg)
{
    if(_bgcolour != bg)
    {
        _bgcolour = bg;
        if(!_text.utf8_empty()) updateTexture_();
    }
}


/** LX_BlendedTextTexture */

LX_BlendedTextTexture::
LX_BlendedTextTexture(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                      uint32_t format)
    : LX_TextTexture(font,w,format) {}


LX_BlendedTextTexture::
LX_BlendedTextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                      LX_Win::LX_Window& w, uint32_t format)
    : LX_BlendedTextTexture(UTF8string(text), font, w, format) {}

LX_BlendedTextTexture::
LX_BlendedTextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                      LX_Win::LX_Window& w, uint32_t format)
    : LX_BlendedTextTexture(text, font.getSize_(), font, w, format) {}


LX_BlendedTextTexture::
LX_BlendedTextTexture(const std::string& text, unsigned int sz,
                      LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                      uint32_t format)
    : LX_BlendedTextTexture(UTF8string(text), sz, font, w, format) {}

LX_BlendedTextTexture::
LX_BlendedTextTexture(const UTF8string& text, unsigned int sz,
                      LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                      uint32_t format)
    : LX_TextTexture(text,sz,font,w,format)
{
    _texture = _font.drawBlendedText_(_text,_size,_win);

    if(_texture == nullptr)
        throw LX_ImageException("LX_BlendedTextTexture — Cannot create the texture: " +
                                  std::string(text.utf8_str()));
}


void LX_BlendedTextTexture::updateTexture_()
{
    const LX_Colour tmp = _font.getColour_();

    if(_texture != nullptr) SDL_DestroyTexture(_texture);
    _font.setColour_(_colour);
    _texture = _font.drawBlendedText_(_text,_size,_win);
    _font.sizeOfText_(_text,_size,_dimension.w,_dimension.h);
    _font.setColour_(tmp);
}

}
