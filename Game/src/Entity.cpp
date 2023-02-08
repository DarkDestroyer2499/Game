#include "Entity.hpp"
#include "Components/ComponentLinker.hpp"

Entity::Entity(sf::RenderTarget* window, const char* newName) :
	mWindow{ window }, mPosition{}
{
	this->AddComponent<TagComponent>(new TagComponent(newName));
}

Entity::~Entity()
{
	for (auto& component : mComponentList)
	{
		delete component;
	}
	Log(INFO, "Entity has been destroyed!");
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
	GraphicsComponent* tmpGraphics = nullptr;
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
		Vec2 size((float)tmpGraphics->GetSprite().getTextureRect().width, (float)tmpGraphics->GetSprite().getTextureRect().height);
		return size;
	}

	return Vec2();
}

float Entity::GetRotation() const
{
	return mRotation;
}

void Entity::Update(const float& ts)
{
	for (auto component : mComponentList)
	{
		component->Update(ts);
	}
}

sf::RenderTarget* Entity::GetWindow()
{
	return mWindow;
}

void Entity::SetRotation(float newRotation)
{
	mRotation = newRotation;
}

bool Entity::IsContainsInBounds(Vec2 pos)
{
	//TODO: finish this
	return false;
}
