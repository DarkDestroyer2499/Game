#ifndef UI_VISUAL_SELECTOR_H
#define UI_VISUAL_SELECTOR_H

#include <SFML/Graphics.hpp>
#include "../Entity.hpp"

constexpr float LENGHT_CORNER_MULT = 3.f;
constexpr float DEFAULT_LINE_WIDTH = 3.f;

enum class CornerType
{
	LEFT_UP,
	LEFT_DOWN,
	RIGHT_UP,
	RIGHT_DOWN
};

class Corner
{
public:
	Corner()
		:mType{ CornerType::LEFT_DOWN }, mWidth{ DEFAULT_LINE_WIDTH }, mColor{ sf::Color::Green }
	{
	}
	~Corner() {}

	void SetParameters(CornerType type, float width = DEFAULT_LINE_WIDTH, sf::Color color = sf::Color::Green)
	{
		mType = type;
		mWidth = width;
		mColor = color;
	}

	void Update(Entity* entity)
	{
		
		Vec2 size = entity->GetSize();
		Vec2 pos = Vec2(entity->GetPosition().x - size.x/2, entity->GetPosition().y - size.y / 2);
		switch (mType)
		{
		case CornerType::LEFT_UP:
			mXLine.setPosition(pos.x - mWidth * 2, pos.y - mWidth * 2);
			mXLine.setSize(sf::Vector2f(mWidth * LENGHT_CORNER_MULT, mWidth));

			mYLine.setPosition(pos.x - mWidth * 2, pos.y - mWidth * 2);
			mYLine.setSize(sf::Vector2f(mWidth, mWidth * LENGHT_CORNER_MULT));
			break;

		case CornerType::LEFT_DOWN:
			mXLine.setPosition(pos.x - mWidth * 2, pos.y + size.y + mWidth);
			mXLine.setSize(sf::Vector2f(mWidth * LENGHT_CORNER_MULT, mWidth));

			mYLine.setPosition(pos.x - mWidth * 2, pos.y + size.y - mWidth);
			mYLine.setSize(sf::Vector2f(mWidth, mWidth * LENGHT_CORNER_MULT));
			break;

		case CornerType::RIGHT_UP:
			mXLine.setPosition(pos.x + size.x + mWidth * 2 - mWidth * LENGHT_CORNER_MULT, pos.y - mWidth * 2);
			mXLine.setSize(sf::Vector2f(mWidth * LENGHT_CORNER_MULT, mWidth));

			mYLine.setPosition(pos.x + size.x + mWidth, pos.y - mWidth * 2);
			mYLine.setSize(sf::Vector2f(mWidth, mWidth * LENGHT_CORNER_MULT));
			break;

		case CornerType::RIGHT_DOWN:
			mXLine.setPosition(pos.x + size.x - mWidth * LENGHT_CORNER_MULT + mWidth * 2, pos.y + size.y + mWidth);
			mXLine.setSize(sf::Vector2f(mWidth * LENGHT_CORNER_MULT, mWidth));

			mYLine.setPosition(pos.x + size.x + mWidth, pos.y + size.y - mWidth);
			mYLine.setSize(sf::Vector2f(mWidth, mWidth * LENGHT_CORNER_MULT));
			break;
		}
		mXLine.setFillColor(mColor);
		mYLine.setFillColor(mColor);
	}

	void Draw(sf::RenderTarget* window)
	{
		window->draw(mXLine);
		window->draw(mYLine);
	}

	void SetColor(sf::Color newColor)
	{
		mColor = newColor;
	}

private:
	float mWidth;
	CornerType mType;
	sf::RectangleShape mXLine, mYLine;
	sf::Color mColor;
};

class UIVisualSelector
{
public:
	UIVisualSelector(float width = DEFAULT_LINE_WIDTH, sf::Color color = sf::Color::Green)
	{
		mCorners[0].SetParameters(CornerType::LEFT_UP, width, color);
		mCorners[1].SetParameters(CornerType::LEFT_DOWN, width, color);
		mCorners[2].SetParameters(CornerType::RIGHT_UP, width, color);
		mCorners[3].SetParameters(CornerType::RIGHT_DOWN, width, color);
	}

	~UIVisualSelector() {};

	void Update(Entity* entity)
	{
		for (auto& corner : mCorners)
		{
			corner.Update(entity);
		}
	}

	void Draw(sf::RenderTarget* window)
	{
		for (auto& corner : mCorners)
		{
			corner.Draw(window);
		}
	}

private:
	Corner mCorners[4];
};

#endif // !UI_VISUAL_SELECTOR_H
