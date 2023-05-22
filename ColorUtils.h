#pragma once

#include <windows.h>
#include <string>

struct Vec4
{
    float r, g, b, a;

    Vec4(float _r, float _g, float _b, float _a)
        : r(_r), g(_g), b(_b), a(_a)
    {}
};

struct WindowInfo
{
    POINT screen_pos;
    POINT window_pos;
    std::string name;
};

class ColorUtils
{
private:

public:

    static Vec4 GetPixelColor();
    static WindowInfo GetHoverInfo();
};

