#ifndef ANIMATED_GRAPHICS_COMPONENT_H
#define ANIMATED_GRAPHICS_COMPONENT_H

#include "IEntityComponent.hpp"
#include "Animation.h"
#include "Graphics.hpp"

namespace Oblivion
{
	class AnimatedGraphicsComponent : public IEntityComponent
	{
	public:
		COMPONENT_TYPE_IMPL(AnimatedGraphicsComponent)

		AnimatedGraphicsComponent();
		AnimatedGraphicsComponent(const AnimatedGraphicsComponent& other);
		AnimatedGraphicsComponent(AnimatedGraphicsComponent&& other) noexcept;
		~AnimatedGraphicsComponent() = default;

		::std::unique_ptr<IEntityComponent> Clone() const override;
		void AddAnimation(const ::std::string& name, sf::Texture& t, Vec2 pos, Vec2 size, int countOfFrames, float speed, float step);
		void SetFlip(bool);
		void Set(const ::std::string&);
		void Update(float) override;
		void Render(sf::RenderTarget* target) override;


		void Pause();
		void Play();

	private:
		::std::string mCurrentAnimation;
		::std::map<::std::string, Animation> mAnimList;
		GraphicsComponent* mGraphicsComponent;

		friend Serializer;
	};
}
#endif // !ANIMATED_GRAPHICS_COMPONENT_H
