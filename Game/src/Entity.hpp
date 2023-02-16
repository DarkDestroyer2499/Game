#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "Components/ComponentLinker.hpp"
#include "Util/Util.hpp"
#include "Util/Log.hpp"

class UI;

class Entity
{
public:
	Entity(sf::RenderTarget* window, const char* newName = "Unknown");
	Entity(const Entity& other) { Log(WARNING, "Entity has been copied!"); };
	virtual ~Entity();

	virtual void Update(const float&);

	void SetPosition(const Vec2&);

	Vec2 GetPosition() const;

	Vec2 GetSize() const;

	void SetRotation(float);

	float GetRotation() const;

	sf::RenderTarget* GetWindow();

	bool IsContainsInBounds(Vec2);

	template<typename Component>
	bool HasComponent()
	{
		for (auto& component : mComponentList)
		{
			if (dynamic_cast<Component*>(component))
				return true;
		}
		return false;
	}

	template<typename Component>
	Component* GetComponent()
	{
		for (auto& component : mComponentList)
		{
			Component* tmp = dynamic_cast<Component*>(component);
			if (tmp)
				return tmp;
		}
		return nullptr;
	}

	template<typename Component, typename... Args>
	Component* AddComponent(Args&&... args)
	{
		Component* tmp = new Component(args...);
		tmp->SetOwner(this);
		mComponentList.push_back(tmp);
		return tmp;
	}

	template<typename Component>
	void RemoveComponent()
	{
		Component* tmpComponent = this->GetComponent<Component>();
		if (tmpComponent != nullptr)
		{
			this->mComponentList.erase(std::remove(this->mComponentList.begin(), this->mComponentList.end(), tmpComponent), this->mComponentList.end());
			delete tmpComponent;
		}
	}

	friend class PropertiesComponent;
	friend class HierarchyComponent;

protected:
	sf::RenderTarget* mWindow;
	std::vector<IComponent*> mComponentList;
	Vec2 mPosition;
	Vec2 mSize;
	float mRotation;
};

#endif // !ENTITY_H
