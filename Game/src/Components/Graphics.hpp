#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "IComponent.hpp"
#include <SFML/Graphics.hpp>

class GraphicsComponent : public IComponent
{
public:
	GraphicsComponent() = delete;
	GraphicsComponent(sf::Texture&, const sf::IntRect&);
	GraphicsComponent(sf::Sprite);
	void Update() override;
	const char* GetName() override;
	~GraphicsComponent() override;

private:
	sf::Sprite mSprite;
};

#endif // !GRAPHICS_COMPONENT_H