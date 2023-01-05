#include "Entity.hpp"
#include "Components/ComponentLinker.hpp"

Entity::Entity(sf::RenderTarget* window, const char* newName) :
	mWindow{ window }, mPosition{}, mName{newName}
{
}

void Entity::SetPosition(const Vec2& newPosition)
{
	mPosition = newPosition;
}

Vec2 Entity::GetPosition() const
{
	return mPosition;
}

Vec2 Entity::GetSize() const
{
	GraphicsComponent* tmpGraphics;
	for (auto& component : mComponentList)
	{
		PhysicsComponent* tmpPhysics = dynamic_cast<PhysicsComponent*>(component);
		
		if (tmpPhysics != nullptr)
		{
			return tmpPhysics->GetSize();
		}		
		tmpGraphics = dynamic_cast<GraphicsComponent*>(component);
	}

	if (tmpGraphics != nullptr)
	{
		Vec2 size(tmpGraphics->GetSprite().getTextureRect().width, tmpGraphics->GetSprite().getTextureRect().height);
		return size;
	}
	return Vec2();
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

bool Entity::IsContainsInBounds(Vec2 pos)
{
	//if(mPosition.x > pos.x && pos.x < mPosition.x + )
	return false;
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
