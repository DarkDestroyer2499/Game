#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "../Util/Util.hpp"

class AnimatedGraphicsComponent;

class Animation
{
public:
	Animation() = default;
	Animation(sf::Texture&, Vec2 pos, Vec2 size, int countOfFrames, float speed, float step);
	~Animation() = default;

	void Update(const float&);
private:
	bool isFlipped, isPlaying;
	float mCurrentFrame, mSpeed;
	std::vector<sf::IntRect> mFrames, mFramesFlipped;
	sf::Sprite mSprite;

	friend AnimatedGraphicsComponent;
};

#endif //!ANIMATION_H
