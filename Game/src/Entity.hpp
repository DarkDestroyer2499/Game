#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "Components/ComponentLinker.hpp"

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

struct Vector2
{
	float x, y;
	Vector2(float x, float y) :x(x), y(y)
	{
	}
	Vector2() :
		x(0.f), y(0.f)
	{
	}

	Vector2(b2Vec2 pos):
		x(pos.x), y(pos.y)
	{
	}
};


class Entity
{
public:
	Entity(sf::RenderTarget* window);
	Entity(const Entity& other) = default;
	virtual ~Entity();

	virtual void Update();

	void SetPosition(const Vector2&);

	Vector2 GetPosition() const;

	sf::RenderTarget* GetWindow();

	template<typename Component>
	void AddComponent(Component *newComponent)
	{
		newComponent->SetOwner(this);
		mComponentList.push_back(newComponent);
	}

protected:
	sf::RenderTarget* mWindow;
	std::vector<IComponent*> mComponentList;
	Vector2 mPosition;
};

#endif // !ENTITY_H
