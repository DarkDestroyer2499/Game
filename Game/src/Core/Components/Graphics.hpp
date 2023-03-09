#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "IEntityComponent.hpp"
#include <SFML/Graphics.hpp>

namespace Oblivion
{
	class GraphicsComponent : public IEntityComponent
	{
	public:
		GraphicsComponent() = delete;
		GraphicsComponent(sf::Texture&, const sf::IntRect&);
		GraphicsComponent(sf::Sprite);
		~GraphicsComponent() override;

		void Update(const float&) override;
		sf::Sprite& GetSprite() { return mSprite; }

	private:
		sf::Sprite mSprite;
	};
}
#endif // !GRAPHICS_COMPONENT_H
