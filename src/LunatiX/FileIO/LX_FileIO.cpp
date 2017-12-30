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
*   @file LX_FileIO.cpp
*   @brief The file handling implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_Error.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rwops.h>

#include <cstring>
#include <cstdio>
#include <cerrno>


namespace LX_FileIO
{

IOException::IOException(std::string err) : _string_error(err) {}

IOException::IOException(const IOException& io) : _string_error(io._string_error) {}

const char * IOException::what() const noexcept
{
    return _string_error.c_str();
}

IOException::~IOException() noexcept {}


/// LX_AbstractFile

LX_AbstractFile::~LX_AbstractFile() {}


/// LX_File

/* Private implementation */

class LX_File_
{
    UTF8string _name;        /* The name of the file         */
    FILE *_fstream;

    void open_(const uint32_t mode)
    {
        std::string str = "LX_File: ";

        if((mode&LX_FILEIO_WRTR) == LX_FILEIO_WRTR)
        {
            _fstream = fopen(_name.utf8_str(), "wb+");
        }
        else if((mode&LX_FILEIO_RDWR) == LX_FILEIO_RDWR)
        {
            _fstream = fopen(_name.utf8_str(), "rb+");
        }
        else if((mode&LX_FILEIO_RDAP) == LX_FILEIO_RDAP)
        {
            _fstream = fopen(_name.utf8_str(), "ab+");
        }
        else if((mode&LX_FILEIO_RDONLY) == LX_FILEIO_RDONLY)
        {
            _fstream = fopen(_name.utf8_str(), "rb");
        }
        else if((mode&LX_FILEIO_WRONLY) == LX_FILEIO_WRONLY)
        {
            _fstream = fopen(_name.utf8_str(), "wb");
        }
        else if((mode&LX_FILEIO_APPEND) == LX_FILEIO_APPEND)
        {
            _fstream = fopen(_name.utf8_str(), "ab");
        }
        else
            throw IOException(str + "Unrecognized mode");

        if(_fstream == nullptr)
            throw IOException(str + LX_GetError());
    }

public:

    LX_File_(const UTF8string& filename, const uint32_t mode)
        : _name(filename), _fstream(nullptr)
    {
        if(mode == 0x00000000)
            throw IOException("LX_File: Invalid mode");

        open_(mode);
    }

    size_t read(void *buffer, size_t dsize, size_t count) noexcept
    {
        return fread(buffer, dsize, count, _fstream);
    }

    size_t readExactly(void *buffer, size_t dsize, size_t count) noexcept
    {
        size_t total_read = 0;
        char * p = static_cast<char *>(buffer);

        // Read at most count bytes
        while(total_read < count)
        {
            size_t read_fstream = read(p, dsize, count);
            p += read_fstream;
            total_read += read_fstream;
        }

        return (total_read != 0 && total_read != count) ?
               static_cast<size_t>(-1) : total_read;
    }

    size_t write(const void *buffer, size_t dsize, size_t count) noexcept
    {
        return fwrite(buffer, dsize, count, _fstream);
    }

    size_t write(const std::string& str) noexcept
    {
        size_t len = str.size();
        return write((void *)str.c_str(), sizeof(char), len);
    }

    bool seek(long offset, int whence) noexcept
    {
        return fseek(_fstream, offset, whence) == 0;
    }

    size_t tell() const noexcept
    {
        return ftell(_fstream);
    }

    size_t size() noexcept
    {
        size_t fsize = static_cast<size_t>(-1);
        size_t old_pos = tell();
        bool ok = seek(0, LX_SEEK_END);

        if(ok) fsize = tell();
        ok = seek(static_cast<long>(old_pos), LX_SEEK_SET);

        if(!ok)
            return static_cast<size_t>(-1);

        return fsize;
    }

    const char * getFilename() const noexcept
    {
        return  _name.utf8_str();
    }

    void close() noexcept
    {
        if(_fstream != nullptr)
        {
            fclose(_fstream);
            _fstream = nullptr;
        }
    }

    ~LX_File_()
    {
        close();
    }
};


/* Public functions */

LX_File::LX_File(const std::string& filename, const uint32_t mode)
    : LX_File(UTF8string(filename), mode) {}

LX_File::LX_File(const UTF8string& filename, const uint32_t mode)
    : _fimpl(new LX_File_(filename, mode)) {}


size_t LX_File::read(void *buffer, size_t dsize, size_t count) noexcept
{
    return _fimpl->read(buffer, dsize, count);
}

size_t LX_File::readExactly(void *buffer, size_t dsize, size_t count) noexcept
{
    return _fimpl->readExactly(buffer, dsize, count);
}


size_t LX_File::write(const void *buffer, size_t dsize, size_t count) noexcept
{
    return _fimpl->write(buffer, dsize, count);
}

size_t LX_File::write(const std::string& str) noexcept
{
    return _fimpl->write(str);
}


bool LX_File::seek(long offset, int whence) noexcept
{
    return _fimpl->seek(offset, whence);
}

size_t LX_File::tell() const noexcept
{
    return _fimpl->tell();
}

size_t LX_File::size() noexcept
{
    return _fimpl->size();
}


const char * LX_File::getFilename() const noexcept
{
    return _fimpl->getFilename();
}


LX_File::~LX_File()
{
    _fimpl->close();
}


/// LX_TmpFile

/* Private implementation */

class LX_TmpFile_
{
    FILE * _f;

public:

    LX_TmpFile_() : _f(tmpfile())
    {
        if(_f == nullptr)
            throw IOException(strerror(errno));
    }

    size_t read(void *buffer, size_t dsize, size_t count) noexcept
    {
        size_t sz = fread(buffer, dsize, count, _f);
        char * err = strerror(errno);

        if(ferror(_f))
            LX_SetError(err);

        return sz;
    }

    size_t readExactly(void *buffer, size_t dsize, size_t count) noexcept
    {
        size_t total_read = 0;
        char * p = static_cast<char *>(buffer);

        // Read at most count bytes
        while(total_read < count)
        {
            size_t read_fstream = read(p, dsize, count);
            p += read_fstream;
            total_read += read_fstream;
        }

        return total_read != count ? 0 : total_read;
    }

    size_t write(const void *buffer, size_t dsize, size_t count) noexcept
    {
        size_t sz = fwrite(buffer, dsize, count, _f);
        char * err = strerror(errno);

        if(ferror(_f))
            LX_SetError(err);

        return sz;
    }

    size_t write(const std::string& str) noexcept
    {
        size_t len = str.size();
        return write((void *)str.c_str(), sizeof(char), len);
    }

    bool seek(long offset, int whence) noexcept
    {
        return fseek(_f, offset, whence) == 0;
    }

    size_t tell() const noexcept
    {
        return ftell(_f);
    }

    ~LX_TmpFile_()
    {
        fclose(_f);
        _f = nullptr;
    }
};


/* Public functions */

LX_TmpFile::LX_TmpFile(): _timpl(new LX_TmpFile_()) {}


size_t LX_TmpFile::read(void *buffer, size_t dsize, size_t count) noexcept
{
    return _timpl->read(buffer, dsize, count);
}

size_t LX_TmpFile::readExactly(void *buffer, size_t dsize, size_t count) noexcept
{
    return _timpl->readExactly(buffer, dsize, count);
}


size_t LX_TmpFile::write(const void *buffer, size_t dsize, size_t count) noexcept
{
    return _timpl->write(buffer, dsize, count);
}

size_t LX_TmpFile::write(const std::string& str) noexcept
{
    return _timpl->write(str);
}


bool LX_TmpFile::seek(long offset, int whence) noexcept
{
    return _timpl->seek(offset, whence);
}

size_t LX_TmpFile::tell() const noexcept
{
    return _timpl->tell();
}

LX_TmpFile::~LX_TmpFile()
{
    _timpl.reset(nullptr);
}


/// Stream
LX_AbstractFile& operator <<(LX_AbstractFile& f, const std::string s) noexcept
{
    f.write(s);
    return f;
}

LX_AbstractFile& operator <<(LX_AbstractFile& f, const UTF8string& u8s) noexcept
{
    f.write(u8s.utf8_str());
    return f;
}

}
