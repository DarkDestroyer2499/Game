#include "Entity.hpp"
#include "Components/IComponent.hpp"

#include <iostream>
Entity::Entity(sf::RenderTarget* window, const char* newName) :
	mWindow{ window }, mPosition{}, mName{newName}
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

void Entity::SetName(const char* newName)
{
	mName = newName;
}

const char* Entity::GetName() const
{
	return mName.c_str();
}

Entity::~Entity() 
{
	for (auto component : mComponentList)
	{
		delete component;
	}
}
