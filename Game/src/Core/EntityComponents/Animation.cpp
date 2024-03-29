#include "Animation.h"
#include "Util/Log.hpp"

namespace Oblivion
{
	Animation::Animation(sf::Texture& t, Vec2 pos, Vec2 size, int countOfFrames, float speed, float step) :
		isFlipped{ false }, isPlaying{ true }, mCurrentFrame{ 0.0f }, mSpeed{ speed }, mStep{ step }, mSize{ size }, mStartPos{ pos }, mTexture{ &t }
	{
		for (int i = 0; i < countOfFrames; ++i)
		{
			mFrames.emplace_back(int(pos.x + i * mStep), (int)pos.y, (int)size.x, (int)size.y);
			mFramesFlipped.emplace_back(int(pos.x + i * mStep + (int)size.x), (int)pos.y, (int)-size.x, (int)size.y);
		}
	}

	void Animation::Update(const float& time)
	{
		if (!isPlaying) return;

		mCurrentFrame += mSpeed * time;

		if (mCurrentFrame > mFrames.size())
			mCurrentFrame -= mFrames.size();

		int tmp = int(mCurrentFrame);

		if (tmp >= mFrames.size())
		{
			Log(ERROR, tmp << " frame not exist! FrameCount: " << mFrames.size() << " TIME: " << time << " CurFrame: " << mCurrentFrame);
			return;
		}
	}

	sf::IntRect Animation::GetTextureRect()
	{
		if (isFlipped)
			return mFramesFlipped[(int)mCurrentFrame];
		else
			return mFrames[(int)mCurrentFrame];
	}

	sf::Texture* Animation::GetTexture()
	{
		return mTexture;
	}
}