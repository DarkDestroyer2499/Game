#pragma once

#include "IComponent.hpp"
#include "Animation.h"

class AnimatedGraphicsComponent : public IComponent
{
public:
	AnimatedGraphicsComponent();
	~AnimatedGraphicsComponent() = default;

	void AddAnimation(const std::string& name, sf::Texture& t, Vec2 pos, Vec2 size, int countOfFrames, float speed, float step);
	void SetFlip(bool);
	void Set(const std::string&);
	void Update(const float &time) override;
	void Pause();
	void Play();

private:
	std::string mCurrentAnimation;
	std::map<std::string, Animation> mAnimList;
};

