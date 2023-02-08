#include "AnimatedGraphics.h"
#include "../Entity.hpp"
AnimatedGraphicsComponent::AnimatedGraphicsComponent()
{
	mName = COMPONENT_NAME;
}

void AnimatedGraphicsComponent::AddAnimation(const std::string& name, sf::Texture& t, Vec2 pos, Vec2 size, int countOfFrames, float speed, float step)
{
	mAnimList[name] = Animation(t, pos, size, countOfFrames, speed, step);
	mCurrentAnimation = name;
}

void AnimatedGraphicsComponent::SetFlip(bool newState)
{
	mAnimList[mCurrentAnimation].isFlipped = newState;
}

void AnimatedGraphicsComponent::Set(const std::string& animName)
{
	if (!mAnimList.contains(animName))
	{
		Log(ERROR, "Animation with name [ " << animName << " ] doest not exist!");
		return;
	}
	mCurrentAnimation = animName;
}

void AnimatedGraphicsComponent::Update(const float &time)
{
	mAnimList[mCurrentAnimation].Update(time);
	mAnimList[mCurrentAnimation].mSprite.setPosition(mOwner->GetPosition().x, mOwner->GetPosition().y);
	mAnimList[mCurrentAnimation].mSprite.setRotation(mOwner->GetRotation() * 57.2957795f);
	mOwner->GetWindow()->draw(mAnimList[mCurrentAnimation].mSprite);
}

void AnimatedGraphicsComponent::Pause()
{
	mAnimList[mCurrentAnimation].isPlaying = false;
}

void AnimatedGraphicsComponent::Play()
{
	mAnimList[mCurrentAnimation].isPlaying = true;
}
