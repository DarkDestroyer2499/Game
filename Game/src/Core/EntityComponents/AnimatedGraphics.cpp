#include "AnimatedGraphics.h"
#include "Core/Entity.hpp"
#include "Core/Engine.hpp"

namespace Oblivion
{
	AnimatedGraphicsComponent::AnimatedGraphicsComponent()
		:mGraphicsComponent{ nullptr }
	{
		mName = COMPONENT_NAME;
	}

	AnimatedGraphicsComponent::AnimatedGraphicsComponent(const AnimatedGraphicsComponent& other)
		: mCurrentAnimation{ other.mCurrentAnimation }, mAnimList{ other.mAnimList }
	{
	}

	AnimatedGraphicsComponent::AnimatedGraphicsComponent(AnimatedGraphicsComponent&& other) noexcept
		: mCurrentAnimation{ std::move(mCurrentAnimation) }
	{
		mAnimList.merge(other.mAnimList);
	}

	::std::unique_ptr<IEntityComponent> AnimatedGraphicsComponent::Clone() const
	{
		return ::std::make_unique<AnimatedGraphicsComponent>(*this);
	}

	void AnimatedGraphicsComponent::AddAnimation(const ::std::string& name, sf::Texture& t, Vec2 pos, Vec2 size, int countOfFrames, float speed, float step)
	{
		mAnimList[name] = Animation(t, pos, size, countOfFrames, speed, step);
		mCurrentAnimation = name;
	}

	void AnimatedGraphicsComponent::SetFlip(bool newState)
	{
		mAnimList[mCurrentAnimation].isFlipped = newState;
	}

	void AnimatedGraphicsComponent::Set(const ::std::string& animName)
	{
		if (!mAnimList.contains(animName))
		{
			Log(ERROR, "Animation with name [ " << animName << " ] doest not exist!");
			return;
		}
		mCurrentAnimation = animName;
	}

	void AnimatedGraphicsComponent::Update(float time)
	{
		if (mGraphicsComponent != nullptr)
		{
			mAnimList[mCurrentAnimation].Update(time);
			sf::Sprite& sprite = mGraphicsComponent->GetSprite();
			sf::IntRect textureRect = mAnimList[mCurrentAnimation].GetTextureRect();
			sprite.setTexture(*mAnimList[mCurrentAnimation].GetTexture());
			sprite.setTextureRect(textureRect);
			sprite.setOrigin({ (float)textureRect.width / 2, (float)textureRect.height / 2 });
			sprite.setPosition(mOwner->GetPosition().x, mOwner->GetPosition().y);
			sprite.setRotation(mOwner->GetRotation() * 57.2957795f);
		}
		else
		{
			mGraphicsComponent = mOwner->GetComponent<GraphicsComponent>();
		}
	}

	void AnimatedGraphicsComponent::Render(sf::RenderTarget* target)
	{
		sf::Sprite& sprite = mGraphicsComponent->GetSprite();



		mOwner->GetEngine()->GetRenderWindow()->draw(sprite);
	}

	void AnimatedGraphicsComponent::Pause()
	{
		mAnimList[mCurrentAnimation].isPlaying = false;
	}

	void AnimatedGraphicsComponent::Play()
	{
		mAnimList[mCurrentAnimation].isPlaying = true;
	}
}