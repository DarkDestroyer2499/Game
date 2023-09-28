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
		GraphicsComponent(const sf::Texture& texture, const sf::IntRect&);
		GraphicsComponent(sf::Sprite);
		GraphicsComponent(const GraphicsComponent& other);
		~GraphicsComponent() = default;

		::std::unique_ptr<IEntityComponent> Clone() const override;
		void Update(const float&) override;
		sf::Sprite& GetSprite();

	private:
		sf::Sprite mSprite;
	};
}
#endif // !GRAPHICS_COMPONENT_H
