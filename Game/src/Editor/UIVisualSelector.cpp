#include "Editor/UIVisualSelector.h"

namespace Oblivion
{
	Corner::Corner()
		:mWidth{ DEFAULT_LINE_WIDTH }, mType{ CornerType::LEFT_DOWN }, mColor{ sf::Color::Green }
	{

	}

	void Corner::SetParameters(CornerType type, float width, sf::Color color)
	{
		mType = type;
		mWidth = width;
		mColor = color;
	}

	void Corner::Update(Entity* entity)
	{
		Vec2 size = entity->GetSize();
		Vec2 pos = Vec2(entity->GetPosition().x - size.x / 2, entity->GetPosition().y - size.y / 2);
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

	void Corner::Draw(sf::RenderTarget* window)
	{
		window->draw(mXLine);
		window->draw(mYLine);
	}

	void Corner::SetColor(sf::Color newColor)
	{
		mColor = newColor;
	}

	//UIVisualSelector

	UIVisualSelector::UIVisualSelector(float width, sf::Color color)
	{
		mCorners[0].SetParameters(CornerType::LEFT_UP, width, color);
		mCorners[1].SetParameters(CornerType::LEFT_DOWN, width, color);
		mCorners[2].SetParameters(CornerType::RIGHT_UP, width, color);
		mCorners[3].SetParameters(CornerType::RIGHT_DOWN, width, color);
	}

	void UIVisualSelector::Update(Entity* entity)
	{
		for (auto& corner : mCorners)
		{
			corner.Update(entity);
		}
	}

	void UIVisualSelector::Draw(sf::RenderTarget* window)
	{
		for (auto& corner : mCorners)
		{
			corner.Draw(window);
		}
	}
}