#pragma once

#include <iostream>
#include <Windows.h>
#include <imgui.h>
#include <string>
#include "Utils.h"
#include <algorithm>

struct HSV {
	float h; // Hue
	float s; // Saturation
	float v; // Value
};

class ColorUtils
{
public:
	static ImVec4 getCurrentPixelColor();
	static ImVec4 getPixelColor(int x, int y);

	static ImVec4 ImVec4To255(const ImVec4& color);
	static ImVec4 ImVec4To01(const ImVec4& color);
	static std::string ImVec4ToHex(const ImVec4& color);
	static HSV RGBtoHSV(float r, float g, float b);
	static std::string ImVec4ToString(const ImVec4& color);
private:
};

