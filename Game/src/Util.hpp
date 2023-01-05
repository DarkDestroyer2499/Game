#ifndef UTIL_HPP
#define UTIL_HPP

#include <imgui.h>
#include <iostream>
#include <SFML/Graphics.hpp>
constexpr float SCALE = 30.f;
constexpr float BORDER_MARGIN = 10.f;
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

	Vec2(sf::Vector2u pos) :
		x((float)pos.x), y((float)pos.y)
	{
	}

	sf::Vector2f ToSFMLVec2f()
	{
		return sf::Vector2f(x, y);
	}

	sf::Vector2u ToSFMLVec2u()
	{
		return sf::Vector2u((unsigned int)x, (unsigned int)y);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec2& vec)
	{
		return os << '[' << vec.x << " : " << vec.y << ']';
	}
};




#endif // !UTIL_HPP
