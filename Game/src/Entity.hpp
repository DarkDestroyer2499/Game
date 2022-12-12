#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <box2d.h>

const float DEG_IN_RAD = 57.29577f;

#define PVARIABLE_GET_SET(type, name)\
	private:\
	type m ## name;\
	public:\
	type Get ## name ## (){\
	return m ## name;\
	}\
	void Set ## name ## (type new ## name){\
	this->m ## name = new ## name;\
	}



class Entity
{
public:
	Entity(sf::Texture&, const sf::IntRect&);
	virtual ~Entity();

	sf::Sprite& GetSprite();
	void SetBody(b2Body*);
	b2Body* GetBody();
	void Update();
	PVARIABLE_GET_SET(int, Name)
protected:
	sf::Sprite mSprite;
	b2Body* mBody;
};

#endif // !ENTITY_H