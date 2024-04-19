#include "ColorUtils.h"

ImVec4 ColorUtils::getCurrentPixelColor()
{
    // Get the device context of the entire screen
    HDC hdcScreen = GetDC(NULL);

    // Get the cursor position
    POINT pt;
    GetCursorPos(&pt);

    // Get the color of the pixel at the cursor position
    COLORREF color = GetPixel(hdcScreen, pt.x, pt.y);

    // Release the device context
    ReleaseDC(NULL, hdcScreen);

    // Extract the RGB components
    int red = GetRValue(color);
    int green = GetGValue(color);
    int blue = GetBValue(color);

    return ImVec4(red, green, blue, 255);
}

ImVec4 ColorUtils::getPixelColor(int x, int y)
{
    // Get the device context of the entire screen
    HDC hdcScreen = GetDC(NULL);

    // Get the color of the pixel at the cursor position
    COLORREF color = GetPixel(hdcScreen, x, y);

    // Release the device context
    ReleaseDC(NULL, hdcScreen);

    // Extract the RGB components
    int red = GetRValue(color);
    int green = GetGValue(color);
    int blue = GetBValue(color);

    return ImVec4(red, green, blue, 255);
}

ImVec4 ColorUtils::ImVec4To255(const ImVec4& color)
{
    return ImVec4(color.x * 255, color.y * 255, color.z * 255, color.w * 255);
}

ImVec4 ColorUtils::ImVec4To01(const ImVec4& color)
{
    return ImVec4(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f);
}

std::string ColorUtils::ImVec4ToHex(const ImVec4& color)
{
    unsigned char r = static_cast<unsigned char>(color.x * 255.0f);
    unsigned char g = static_cast<unsigned char>(color.y * 255.0f);
    unsigned char b = static_cast<unsigned char>(color.z * 255.0f);
    
    char hex[8];
    snprintf(hex, sizeof(hex), "#%02X%02X%02X", r, g, b);
    return std::string(hex);
}

HSV ColorUtils::RGBtoHSV(float r, float g, float b)
{
    HSV hsv;

    // Find the minimum and maximum values among r, g, and b
    std::vector<float> color_vec{ r, g, b };
    float minVal = *std::min_element(color_vec.begin(), color_vec.end());
    float maxVal = *std::max_element(color_vec.begin(), color_vec.end());
    float delta = maxVal - minVal;

    // Calculate Hue
    if (delta == 0) // Undefined hue for grayscale
        hsv.h = 0;
    else if (maxVal == r)
        hsv.h = 60 * fmod(((g - b) / delta), 6);
    else if (maxVal == g)
        hsv.h = 60 * (((b - r) / delta) + 2);
    else if (maxVal == b)
        hsv.h = 60 * (((r - g) / delta) + 4);

    // Make sure hue is in the range [0, 360)
    if (hsv.h < 0)
        hsv.h += 360;

    // Calculate Saturation
    if (maxVal == 0)
        hsv.s = 0;
    else
        hsv.s = delta / maxVal;

    // Calculate Value
    hsv.v = maxVal;

    return hsv;
}

std::string ColorUtils::ImVec4ToString(const ImVec4& color)
{
    std::string str_color = "{" + std::to_string(color.x) + "," + std::to_string(color.y) + "," + std::to_string(color.z) + "}";
    return str_color;
}


