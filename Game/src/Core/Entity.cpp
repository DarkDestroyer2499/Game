#include "Core/Entity.hpp"
#include "Components/ComponentLinker.hpp"

namespace Oblivion
{

	Entity::Entity(Engine* engine, const char* newName) :
		mEngine{engine},mPosition {}, ecs{ this }
	{
		this->ecs.AddComponent<TagComponent>(newName);
		this->ecs.AddComponent<TransformComponent>();
		this->ecs.AddComponent<IDComponent>();
	}

	Entity::~Entity()
	{
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

	Vec2 Entity::GetSize()
	{
		GraphicsComponent* tmpGraphics = nullptr;
		for (const auto& component : ecs.GetComponentList())
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

	Engine* Entity::GetEngine()
	{
		return mEngine;
	}

	void Entity::Update(const float& ts)
	{
		for (auto& component : ecs.GetComponentList())
		{
			component->Update(ts);
		}
	}

	void Entity::SetRotation(float newRotation)
	{
		mRotation = newRotation;
	}
}