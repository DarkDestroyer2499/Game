#include "Transform.hpp"
#include "Core/Entity.hpp"

namespace Oblivion
{
	TransformComponent::TransformComponent()
		: position{}, rotation{}, mLastPosition{}, mLastRotation{}
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

	void TransformComponent::Update(float ts)
	{
		if (position != mLastPosition || rotation != mLastRotation)
		{
			NotifyTransformChanged();
			mLastPosition = position;
			mLastRotation = rotation;
		}
	}

	void TransformComponent::Render(sf::RenderTarget* target)
	{
	}

	void TransformComponent::SubscribeToTransformChanged(const TransformChangedCallback& callback)
	{
		mTransformChangedCallbacks.push_back(callback);
	}

	void TransformComponent::SetPosition(const Vec2& pos)
	{
		if (position != pos)
		{
			position = pos;
			mLastPosition = pos;
			NotifyTransformChanged();
		}
	}

	void TransformComponent::SetRotation(float rot)
	{
		if (rotation != rot)
		{
			rotation = rot;
			mLastRotation = rot;
			NotifyTransformChanged();
		}
	}

	void TransformComponent::SetPositionSilent(const Vec2& pos)
	{
		position = pos;
		mLastPosition = pos;
	}

	void TransformComponent::SetRotationSilent(float rot)
	{
		rotation = rot;
		mLastRotation = rot;
	}

	void TransformComponent::NotifyTransformChanged()
	{
		for (const auto& callback : mTransformChangedCallbacks)
		{
			callback(position, rotation);
		}
	}
}