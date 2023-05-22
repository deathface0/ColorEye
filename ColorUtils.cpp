#include "ColorUtils.h"

Vec4 ColorUtils::GetPixelColor()
{
    HWND hwnd = GetDesktopWindow();
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    HDC hdc = GetDC(hwnd);
    COLORREF pixelColor = GetPixel(hdc, cursorPos.x, cursorPos.y);
    ReleaseDC(hwnd, hdc);

    float red = static_cast<float>(GetRValue(pixelColor)) / 255.0f;
    float green = static_cast<float>(GetGValue(pixelColor)) / 255.0f;
    float blue = static_cast<float>(GetBValue(pixelColor)) / 255.0f;
    float alpha = 1.0f;

    return Vec4(red, green, blue, alpha);
}

WindowInfo ColorUtils::GetHoverInfo()
{
    POINT windowPos, screenPos;
    GetCursorPos(&screenPos); // Obtener la posición actual del cursor

    HWND hwnd = WindowFromPoint(screenPos); // Obtener el HWND de la ventana bajo el cursor
    windowPos = screenPos;
    ScreenToClient(hwnd, &screenPos);

    int length = GetWindowTextLengthW(hwnd);
    std::string windowName(length + 1, L'\0');
    GetWindowTextA(hwnd, &windowName[0], length + 1);

    return {screenPos, windowPos, windowName};
}
