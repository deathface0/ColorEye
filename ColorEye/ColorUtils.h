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

template<typename T>
struct Vec3
{
	T x, y, z;

	Vec3(T x, T y, T z)
		:x(x), y(y), z(z) {}

	std::string to_string()
	{
		std::string vecStr = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);
		return vecStr;
	}

	ImVec4 to_ImVec4()
	{
		ImVec4 vec({ x, y, z, 0 });
		return vec;
	}

	void importHSV(HSV hsv)
	{
		this->x = hsv.h;
		this->y = hsv.s;
		this->z = hsv.v;
	}
};

class ColorUtils
{
public:
	static Vec3<int> getCurrentPixelColor();
	static Vec3<int> getPixelColor(int x, int y);

	static Vec3<int> rgb01To255(const Vec3<float>& color);
	static Vec3<float> rgb255To01(const Vec3<int>& color);
	static std::string rgb01ToHex(const Vec3<float>& color);
	static std::string rgb255ToHex(const Vec3<int>& color);
	static HSV rgb255toHSV(float r, float g, float b);

private:
};

