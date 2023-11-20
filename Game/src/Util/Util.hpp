#ifndef UTIL_HPP
#define UTIL_HPP

#include <imgui.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d.h>

namespace Oblivion {

	constexpr float BORDER_MARGIN = 10.f;

	const float DEG_IN_RAD = 57.29577f;

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

		Vec2(sf::Vector2i pos) :
			x((float)pos.x), y((float)pos.y)
		{
		}

		Vec2(sf::Vector2f pos) :
			x(pos.x), y(pos.y)
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

		sf::Vector2i ToSFMLVec2i()
		{
			return sf::Vector2i((int)x, (int)y);
		}

		Vec2 operator/(float i)
		{
			return { x / i, y / i };
		}

		Vec2 operator-(Vec2 other)
		{
			return { x - other.x, y - other.y };
		}

		Vec2 operator+(Vec2 other)
		{
			return { x + other.x, y + other.y };
		}

		friend ::std::ostream& operator<<(::std::ostream& os, const Vec2& vec)
		{
			return os << '[' << vec.x << " : " << vec.y << ']';
		}
	};

#define PVARIABLE_GET_SET(type, name)\
	private:\
	type m ## name;\
	public:\
	type Get ## name ## (){\
	return m ## name;\
	}\
	void Set ## name ## (type new ## name){\
	this->m ## name = new ## name;\
	}
}
#endif // !UTIL_HPP
