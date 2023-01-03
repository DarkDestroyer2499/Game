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

	Vector2(b2Vec2 pos) :
		x(pos.x), y(pos.y)
	{
	}
};
#include <iostream>
class UI;
class Entity
{
public:
	Entity(sf::RenderTarget* window, const char* newName = "Unknown");
	Entity(const Entity& other) { std::cout << "COPY\n\n"; };
	virtual ~Entity();

	virtual void Update();

	void SetPosition(const Vector2&);

	Vector2 GetPosition() const;

	sf::RenderTarget* GetWindow();

	template<typename Component>
	bool HasComponent()
	{
		for (auto component : mComponentList)
		{
			if (dynamic_cast<Component*>(component))
				return true;
		}
		return false;
	}

	template<typename Component>
	Component* GetComponent()
	{
		for (auto component : mComponentList)
		{
			Component* tmp = dynamic_cast<Component*>(component);
			if (tmp)
				return tmp;
		}
		return nullptr;
	}

	template<typename Component>
	void AddComponent(Component* newComponent)
	{
		newComponent->SetOwner(this);
		mComponentList.push_back(newComponent);
	}

	void SetName(const char*);

	const char* GetName() const;

	friend class UI;

protected:
	sf::RenderTarget* mWindow;
	std::vector<IComponent*> mComponentList;
	Vector2 mPosition;
	std::string mName;
};

#endif // !ENTITY_H
