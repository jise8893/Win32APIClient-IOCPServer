#pragma once
#include <assert.h>
struct Vec2
{
	float x;
	float y;
public:
	Vec2() :x(0.f), y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(int _x, int _y) :x((float)_x), y((float)_y) {}
public:
	Vec2& operator = (POINT pt)
	{
		x = pt.x;
		y = pt.y;
	}
	Vec2 operator + (Vec2 vOther)
	{
		return Vec2(x + vOther.x, y + vOther.y);
	}
	Vec2 operator += (Vec2 vOther)
	{
		x += vOther.x;
		y += vOther.y;
		return Vec2(x, y);
	}
	Vec2 operator - (Vec2 vOther)
	{
		return Vec2(x - vOther.x, y - vOther.y);
	}
	Vec2 operator * (Vec2 vOther)
	{
		return Vec2(x * vOther.x, y * vOther.y);
	}
	Vec2 operator / (Vec2 vOther)
	{
		assert(!(vOther.x == 0.f || vOther.y == 0.f));
		return Vec2(x / vOther.x, y / vOther.y);
	}
	Vec2 operator / (float vOther)
	{
		assert(!(vOther == 0.f));
		return Vec2(x / vOther, y / vOther);
	}

	Vec2 operator * (int i)
	{
		return Vec2(x * float(i), y * float(i));
	}
	Vec2(POINT pt)
	{
		x = (float)pt.x;
		y = (float)pt.y;
	}
public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}
	Vec2& Normalize()
	{
		float fLen = Length();

		assert(fLen != 0.f);
		x /= fLen; y /= fLen;



		return *this;
	}
};