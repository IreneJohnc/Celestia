// overlay.h
//
// Copyright (C) 2001, Chris Laurel <claurel@shatters.net>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

#ifndef _OVERLAY_H_
#define _OVERLAY_H_

#include <string>
#include <iostream>
#include <celtxf/texturefont.h>


class Overlay;

// Custom streambuf class to support C++ operator style output.  The
// output is completely unbuffered so that it can coexist with printf
// style output which the Overlay class also supports.
class OverlayStreamBuf : public std::streambuf
{
 public:
    OverlayStreamBuf();

    void setOverlay(Overlay*);

    int overflow(int c = EOF);

    enum UTF8DecodeState
    {
        UTF8DecodeStart     = 0,
        UTF8DecodeMultibyte = 1,
    };

 private:
    Overlay* overlay{ nullptr };

    UTF8DecodeState decodeState{ UTF8DecodeStart };
    wchar_t decodedChar{ 0 };
    unsigned int decodeShift{ 0 };
};


class Overlay : public std::ostream
{
 public:
    Overlay();
    ~Overlay() = default;

    void begin();
    void end();

    void setWindowSize(int, int);
    void setFont(TextureFont*);

    void rect(float x, float y, float w, float h, bool fill = true);

    void beginText();
    void endText();
    void print(wchar_t);
    void print(char);
    void print(const char*);

 private:
    int windowWidth{ 1 };
    int windowHeight{ 1 };
    TextureFont* font{ nullptr };
    bool useTexture{ false };
    bool fontChanged{ false };
    int textBlock{ 0 };

    float xoffset{ 0.0f };
    float yoffset{ 0.0f };

    OverlayStreamBuf sbuf;
};

#endif // _OVERLAY_H_
