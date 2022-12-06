#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual sf::Sprite& GetSprite() = 0;
	virtual void Draw() = 0;
	virtual ~Entity();

};

#endif // !ENTITY_H