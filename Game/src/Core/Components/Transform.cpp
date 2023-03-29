#include "Transform.hpp"
#include "Core/Entity.hpp"

namespace Oblivion
{
	TransformComponent::TransformComponent()
	{
		mName = COMPONENT_NAME;
	}

	TransformComponent::~TransformComponent()
	{
	}

	::std::unique_ptr<IEntityComponent> TransformComponent::Clone() const
	{
		return ::std::make_unique<TransformComponent>();
	}

	void TransformComponent::Update(const float& ts)
	{
	}

	void TransformComponent::SetPosition(Vec2 newPosition)
	{
		auto physicsComponent = mOwner->ecs.GetComponent<PhysicsComponent>();
		if (physicsComponent)
		{
			physicsComponent->SetPosition(newPosition);
		}
		else
		{
			auto graphicsComponent = mOwner->ecs.GetComponent<GraphicsComponent>();
			if (graphicsComponent)
			{
				graphicsComponent->GetSprite().setPosition(newPosition.ToSFMLVec2f());
			}
			else
			{
				Log(ERROR, "No components to set position!");
			}
		}
	}

	Vec2 TransformComponent::GetPosition()
	{
		auto physicsComponent = mOwner->ecs.GetComponent<PhysicsComponent>();
		if (physicsComponent)
		{
			return physicsComponent->GetPosition();
		}
		else
		{
			auto graphicsComponent = mOwner->ecs.GetComponent<GraphicsComponent>();
			if (graphicsComponent)
			{
				return graphicsComponent->GetSprite().getPosition();
			}
			else
			{
				Log(ERROR, "No components to get position!");
				return Vec2();
			}
		}
	}

	void TransformComponent::SetRotation(float newRotation)
	{
		auto physicsComponent = mOwner->ecs.GetComponent<PhysicsComponent>();
		if (physicsComponent)
		{
			physicsComponent->SetRotation(newRotation);
		}
		else
		{
			auto graphicsComponent = mOwner->ecs.GetComponent<GraphicsComponent>();
			if (graphicsComponent)
			{
				graphicsComponent->GetSprite().setRotation(newRotation);
			}
			else
			{
				Log(ERROR, "No components to set rotation!");
			}
		}
	}

	float TransformComponent::GetRotation()
	{
		auto physicsComponent = mOwner->ecs.GetComponent<PhysicsComponent>();
		if (physicsComponent)
		{
			return physicsComponent->GetRotation();
		}
		else
		{
			auto graphicsComponent = mOwner->ecs.GetComponent<GraphicsComponent>();
			if (graphicsComponent)
			{
				return graphicsComponent->GetSprite().getRotation();
			}
			else
			{
				Log(ERROR, "No components to get rotation!");
				return 0.f;
			}
		}
	}
}