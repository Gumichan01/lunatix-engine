
#include <LunatiX/utils/libtagspp/libtagspp.hpp>
#include <LunatiX/utils/libtagspp/tags.h>

#include <sstream>
#include <cstdio>

namespace
{

struct Aux
{
    FILE * f;
    libtagpp::Tag& tag;
};

int ctxread(Tagctx *ctx, void *buf, int cnt)
{
    Aux *aux = static_cast<Aux *>(ctx->aux);
    return static_cast<int>(fread(buf,1,static_cast<size_t>(cnt),aux->f));
}

int ctxseek(Tagctx *ctx, int offset, int whence)
{
    Aux *aux = static_cast<Aux *>(ctx->aux);
    fseek(aux->f, offset, whence);
    return static_cast<int>(ftell(aux->f));
}

inline const char * sec_(int second)
{
    return second < 10 ? "0":"";
}

inline const char * minute_(int minute)
{
    return minute < 10 ? "0":"";
}

std::string duration(int t)
{
    std::ostringstream ss;
    const int H_MINUTE = 60;
    const int M_SECOND = 60;
    const int d = t / 1000;
    int hour, minute, second;

    hour = 0;
    minute = 0;
    second = 0;

    if(d > M_SECOND)
    {
        minute = d / M_SECOND;
        second = d % M_SECOND;

        if(minute > H_MINUTE)
        {
            hour = minute / H_MINUTE;
            minute = minute % H_MINUTE;
        }
    }
    else
        second = d;

    if(hour > 0)
        ss << hour << ":" << minute_(minute) << minute << ":" << sec_(second) << second;
    else if(minute > 0)
        ss << minute << ":" << sec_(second) << second;
    else
        ss << second << "s";

    return ss.str();
}

std::string format(int f)
{
    std::string s;

    switch(f)
    {
    case 0:
        s = "MP3";
        break;
    case 1:
        s = "OGG Vorbis";
        break;
    case 2:
        s = "FLAC";
        break;
    case 3:
        s = "M4A";
        break;
    default:
        s = "UNKNOWN";
        break;
    }

    return s;
}

}

namespace libtagpp
{

/* Properties */

Properties::Properties()
    : channels(0), samplerate(0), bitrate(0), duration(""), format("") {}


/* Tag */

// (Tag) Friend function
void ctxtag(Tagctx *ctx, int t, const char *v, int offset, int size, Tagread f)
{
    Aux *aux = (Aux *) ctx->aux;

    switch(t)
    {
    case Tartist:
        aux->tag._artist = v;
        break;
    case Talbum:
        aux->tag._album = v;
        break;
    case Ttitle:
        aux->tag._title = v;
        break;
    case Tdate:
        aux->tag._year = v;
        break;
    case Ttrack:
        aux->tag._track = v;
        break;
    case Tgenre:
        aux->tag._genre = v;
        break;
    case Talbumgain:
        aux->tag._albumgain = v;
        break;
    case Talbumpeak:
        aux->tag._albumpeak = v;
        break;
    case Ttrackgain:
        aux->tag._trackgain = v;
        break;

    case Timage:
        aux->tag._imdata._img_offset = offset;
        aux->tag._imdata._img_size = size;
        break;
    default:
        break;
    }
}


Tag::Tag(): _imdata({0,0}) {}


bool Tag::readTag(const std::string& filename)
{
    const char * f = filename.c_str();
    char buf[256];
    Aux aux = { NULL, *this };
    Tagctx ctx = { NULL, ctxread, ctxseek, ctxtag, &aux, buf, sizeof(buf),
                   0, 0, 0, 0, 0, 0, 0
                 };

    if((aux.f = fopen(f, "rb")) == NULL)
    {
        fprintf(stderr, "failed to open: %s does not exist\n",f);
        return false;
    }

    bool success = tagsget(&ctx) == 0;
    fclose(aux.f);

    if(success)
    {
        _properties.channels   = ctx.channels;
        _properties.samplerate = ctx.samplerate;
        _properties.bitrate    = ctx.bitrate;
        _properties.duration   = duration(ctx.duration);
        _properties.format     = format(ctx.format);
        return true;
    }

    return false;
}


const char * Tag::title() const
{
    return _title.c_str();
}

const char * Tag::artist() const
{
    return _artist.c_str();
}

const char * Tag::album() const
{
    return _album.c_str();
}

const char * Tag::year() const
{
    return _year.c_str();
}

const char * Tag::track() const
{
    return _track.c_str();
}

const char * Tag::genre() const
{
    return _genre.c_str();
}

const char * Tag::albumgain() const
{
    return _albumgain.c_str();
}

const char * Tag::albumpeak() const
{
    return _albumpeak.c_str();
}

const char * Tag::trackgain() const
{
    return _trackgain.c_str();
}

const char * Tag::trackpeak() const
{
    return _trackpeak.c_str();
}

const ImgMetaData& Tag::getImageMetaData() const
{
    return _imdata;
}

const Properties& Tag::properties() const
{
    return _properties;
}

}
