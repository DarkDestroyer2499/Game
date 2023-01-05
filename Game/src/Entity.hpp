#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "Components/ComponentLinker.hpp"
#include "Util.hpp"
#include "Log.hpp"

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



class UI;
class Entity
{
public:
	Entity(sf::RenderTarget* window, const char* newName = "Unknown");
	Entity(const Entity& other) { Log(WARNING, "Entity has been copied!"); };
	virtual ~Entity();

	virtual void Update();

	void SetPosition(const Vec2&);

	Vec2 GetPosition() const;

	Vec2 GetSize() const;

	sf::RenderTarget* GetWindow();

	bool IsContainsInBounds(Vec2);

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
	Vec2 mPosition;
	Vec2 mSize;
	std::string mName;
};

#endif // !ENTITY_H
