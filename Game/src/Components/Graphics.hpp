#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "IComponent.hpp"
#include <SFML/Graphics.hpp>
#include "../Entity.hpp"
class GraphicsComponent : public IComponent
{
public:
	GraphicsComponent() = delete;
	GraphicsComponent(sf::Texture&, const sf::IntRect&);
	GraphicsComponent(sf::Sprite);
	~GraphicsComponent() override;
	void Update() override;
	sf::Sprite& GetSprite() { return mSprite; }
	const char* GetName() override;

private:
	sf::Sprite mSprite;
};

#endif // !GRAPHICS_COMPONENT_H