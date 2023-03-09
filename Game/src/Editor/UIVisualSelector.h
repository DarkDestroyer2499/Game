#ifndef UI_VISUAL_SELECTOR_H
#define UI_VISUAL_SELECTOR_H

#include <SFML/Graphics.hpp>
#include "Core/Entity.hpp"

namespace Oblivion
{
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
		Corner();
		~Corner() = default;

		void SetParameters(CornerType type, float width = DEFAULT_LINE_WIDTH, sf::Color color = sf::Color::Green);

		void Update(Entity* entity);

		void Draw(sf::RenderTarget* window);

		void SetColor(sf::Color newColor);

	private:
		float mWidth;
		CornerType mType;
		sf::RectangleShape mXLine, mYLine;
		sf::Color mColor;
	};

	class UIVisualSelector
	{
	public:
		UIVisualSelector(float width = DEFAULT_LINE_WIDTH, sf::Color color = sf::Color::Green);

		~UIVisualSelector() = default;

		void Update(Entity* entity);

		void Draw(sf::RenderTarget* window);

	private:
		Corner mCorners[4];
	};
}
#endif // !UI_VISUAL_SELECTOR_H
