#include "Entity.hpp"
#include "Components/IComponent.hpp"

Entity::Entity(sf::RenderTarget* window) : 
	mWindow{ window }, mPosition{}
{
}

void Entity::SetPosition(const Vector2& newPosition)
{
	mPosition = newPosition;
}

Vector2 Entity::GetPosition() const
{
	return mPosition;
}

void Entity::Update()
{
	for (auto component : mComponentList)
	{
		component->Update();
	}
}

sf::RenderTarget* Entity::GetWindow()
{
	return mWindow;
}

Entity::~Entity() 
{
	for (auto component : mComponentList)
	{
		delete component;
	}
}
