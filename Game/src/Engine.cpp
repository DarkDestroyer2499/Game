#include "Engine.hpp"
#include "Log.h"
Engine::Engine(ScreenMode wMode, unsigned int width = 0, unsigned int height = 0):
	mWindowMode{ wMode }, mScnWidht{ sf::VideoMode::getDesktopMode().width / 2 }, mScnHeight{ sf::VideoMode::getDesktopMode().height / 2 }, mWorking{true}
{
}


void Engine::Run()
{
	mWindow.create(sf::VideoMode(mScnWidht, mScnHeight), WINDOW_NAME, mWindowMode);
	Log(ERROR) << "Engine has been started" << 1 << 2 << 3;
	while (mWindow.isOpen())
	{
		
		while (mWindow.pollEvent(mEvent))
		{
			if (mEvent.type == sf::Event::Closed || mWorking == false)
				mWindow.close();
		}
		mWindow.display();
	}
}

sf::RenderWindow& Engine::GetWindow()
{
	return mWindow;
}

void Engine::SetScreenMode(ScreenMode newMode)
{
	mWindow.create(sf::VideoMode(mScnWidht, mScnHeight), WINDOW_NAME, newMode);
}

void Engine::Stop()
{
	
}
