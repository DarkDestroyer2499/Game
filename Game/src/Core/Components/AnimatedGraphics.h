#ifndef ANIMATED_GRAPHICS_COMPONENT_H
#define ANIMATED_GRAPHICS_COMPONENT_H

#include "IEntityComponent.hpp"
#include "Animation.h"

namespace Oblivion
{
	class AnimatedGraphicsComponent : public IEntityComponent
	{
	public:
		AnimatedGraphicsComponent();
		~AnimatedGraphicsComponent() = default;

		void AddAnimation(const ::std::string& name, sf::Texture& t, Vec2 pos, Vec2 size, int countOfFrames, float speed, float step);
		void SetFlip(bool);
		void Set(const ::std::string&);
		void Update(const float& time) override;
		void Pause();
		void Play();

	private:
		::std::string mCurrentAnimation;
		::std::map<::std::string, Animation> mAnimList;
	};
}
#endif // !ANIMATED_GRAPHICS_COMPONENT_H
