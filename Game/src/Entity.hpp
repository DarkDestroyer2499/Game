#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(sf::Sprite&);
	Entity(sf::Texture&, const sf::IntRect&);
	sf::Sprite& GetSprite();
	virtual ~Entity();
protected:
	sf::Sprite mSprite;
};

#endif // !ENTITY_H