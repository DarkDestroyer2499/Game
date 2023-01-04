#ifndef UTIL_HPP
#define UTIL_HPP

#include <imgui.h>
#include <iostream>
constexpr float SCALE = 30.f;

struct Vec2
{
	float x, y;
	Vec2(float x, float y) :x(x), y(y)
	{
	}
	Vec2(ImVec2 vec) :
		x(vec.x), y(vec.y)
	{
	}
	Vec2() :
		x(0.f), y(0.f)
	{
	}

	Vec2(b2Vec2 pos) :
		x(pos.x), y(pos.y)
	{
	}
	friend std::ostream& operator<<(std::ostream& os, const Vec2& vec)
	{
		return os << '[' << vec.x << " : " << vec.y << ']';
	}
};




#endif // !UTIL_HPP
