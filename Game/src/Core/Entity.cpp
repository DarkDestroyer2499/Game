#include "Core/Entity.hpp"
#include "EntityComponents/ComponentLinker.hpp"
#include "Core/Engine.hpp"

namespace Oblivion
{
	Entity::Entity()
		: mEngine{ nullptr }, mPosition{}, ecs{ nullptr }, mRotation{}, rm{ nullptr }

	{
		this->ecs.AddComponent<TagComponent>("");
		this->transform = std::make_unique<TransformComponent>();
		this->transform->SetOwner(this);
		//this->ecs.AddComponent<TransformComponent>();
	}

	Entity::Entity(Engine* engine, const char* newName) :
		mEngine{ engine }, mPosition{}, ecs{ this }, mRotation{}
	{
		this->ecs.AddComponent<TagComponent>(newName);
		//this->ecs.AddComponent<TransformComponent>();
		this->transform = std::make_unique<TransformComponent>();
		this->transform->SetOwner(this);

		rm = &mEngine->resourceManager;
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

	void Entity::SetUUID(UUID uuid)
	{
		mUUID = uuid;
	}

	UUID Entity::GetUUID()
	{
		return mUUID;
	}

	Entity::Entity(const Entity& other)
	{
		rm = other.rm;
		ecs = other.ecs;
		mEngine = other.mEngine;
		mRotation = 0;
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
		rm = other.rm;
		ecs = other.ecs;
		mEngine = other.mEngine;
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
		mRotation = newRotation;
	}
}