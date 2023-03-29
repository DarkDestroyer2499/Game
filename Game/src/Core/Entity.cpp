#include "Core/Entity.hpp"
#include "Components/ComponentLinker.hpp"
#include "Core/Engine.hpp"

namespace Oblivion
{
	Entity::Entity()
		: mEngine{ nullptr }, mPosition{}, ecs{ nullptr }, mRotation{}, rm{nullptr}

	{
		this->ecs.AddComponent<TagComponent>("");
		this->ecs.AddComponent<TransformComponent>();
		this->ecs.AddComponent<IDComponent>();
	}

	Entity::Entity(Engine* engine, const char* newName) :
		mEngine{ engine }, mPosition{}, ecs{ this }, mRotation{}
	{
		this->ecs.AddComponent<TagComponent>(newName);
		this->ecs.AddComponent<TransformComponent>();
		this->ecs.AddComponent<IDComponent>();

		rm = &mEngine->resourceManager;
	}

	Entity::Entity(const Entity& other):
		mEngine{other.mEngine}, mPosition{other.mPosition}, ecs{other.ecs}, mRotation{}
	{
		rm = &other.mEngine->resourceManager;
		Log(ERROR, "Entity has been copied!");
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

	Entity& Entity::operator=(const Entity& other)
	{
		return *this;
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