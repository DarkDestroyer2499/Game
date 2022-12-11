#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <box2d.h>

class Entity
{
public:
	Entity(sf::Texture&, const sf::IntRect&);
	sf::Sprite& GetSprite();
	void SetBody(b2Body*);
	b2Body* GetBody();
	virtual ~Entity();
protected:
	sf::Sprite mSprite;
	b2Body* mBody;
};

#endif // !ENTITY_H