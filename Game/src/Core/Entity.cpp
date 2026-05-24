#include "Core/Entity.hpp"
#include "EntityComponents/ComponentLinker.hpp"
#include "Core/Engine.hpp"

namespace Oblivion
{
	Entity::Entity()
		: mEngine{ nullptr }, ecs{ this }, rm{ nullptr }
	{
		this->ecs.AddComponent<TagComponent>("");
		this->ecs.AddComponent<TransformComponent>();
	}

	Entity::Entity(Engine* engine, const char* newName) :
		mEngine{ engine }, ecs{ this }
	{
		this->ecs.AddComponent<TagComponent>("");
		this->ecs.AddComponent<TransformComponent>();

		rm = &mEngine->resourceManager;
	}

	Entity::~Entity()
	{
		Log(INFO, "Entity has been destroyed!");
	}


	void Entity::SetPosition(const Vec2& newPosition)
	{
		GetTransform()->position = newPosition;
	}

	Vec2 Entity::GetPosition()
	{
		return GetTransform()->position;
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

	float Entity::GetRotation()
	{
		return GetTransform()->rotation;
	}

	Engine* Entity::GetEngine()
	{
		return mEngine;
	}

	void Entity::SetUUID(UUID uuid)
	{
		mUUID = uuid;
	}

	UUID Entity::GetUUID()
	{
		return mUUID;
	}

	TransformComponent* Entity::GetTransform()
	{
		return ecs.GetComponent<TransformComponent>();
	}

	Entity::Entity(const Entity& other)
		: rm(other.rm)
		, ecs(this)
		, mEngine(other.mEngine)
		, mUUID()
	{
		ecs = other.ecs;
	}

	ECS<IEntityComponent, Entity*>& Entity::GetEcs()
	{
		return ecs;
	}

	void Entity::LoadEcs(ECS<IEntityComponent, Entity*>& newEcs)
	{
		ecs = newEcs;
	}

	Entity& Entity::operator=(const Entity& other)
	{
		if (this == &other)
			return *this;

		rm = other.rm;
		mEngine = other.mEngine;

		ecs = other.ecs;

		return *this;
	}

	void Entity::Update(float ts)
	{
		for (auto& component : ecs.GetComponentList())
		{
			component->Update(ts);
			component->Render(mEngine->GetRenderWindow());
		}
	}

	void Entity::SetRotation(float newRotation)
	{
		GetTransform()->rotation = newRotation;
	}
}