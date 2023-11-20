#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "Util/Util.hpp"

namespace Oblivion
{
	class AnimatedGraphicsComponent;
	class Serializer;

	class Animation
	{
	public:
		Animation() = default;
		Animation(sf::Texture&, Vec2 pos, Vec2 size, int countOfFrames, float speed, float step);
		~Animation() = default;

		void Update(const float&);

		sf::IntRect GetTextureRect();

		sf::Texture* GetTexture();
		
	private:
		bool isFlipped, isPlaying;
		float mCurrentFrame, mSpeed, mStep;
		::std::vector<sf::IntRect> mFrames, mFramesFlipped;
		Vec2 mSize, mStartPos;
		sf::Texture *mTexture;

		friend AnimatedGraphicsComponent;
		friend Serializer;
	};
}
#endif //!ANIMATION_H
