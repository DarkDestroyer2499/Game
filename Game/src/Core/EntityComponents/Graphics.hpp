#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "IEntityComponent.hpp"
#include <SFML/Graphics.hpp>

namespace Oblivion
{
	class GraphicsComponent : public IEntityComponent
	{
	public:
		COMPONENT_TYPE_IMPL(GraphicsComponent)

		GraphicsComponent();
		GraphicsComponent(const sf::Texture& texture, const sf::IntRect&);
		GraphicsComponent(sf::Sprite);
		GraphicsComponent(const GraphicsComponent& other);
		~GraphicsComponent() = default;

		::std::unique_ptr<IEntityComponent> Clone() const override;
		void Update(float) override;
		void Render(sf::RenderTarget* target) override;



		sf::Sprite& GetSprite();

	private:
		sf::Sprite mSprite;
	};
}
#endif // !GRAPHICS_COMPONENT_H
