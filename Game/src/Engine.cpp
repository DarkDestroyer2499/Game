#include "Engine.hpp"
#include "Log.h"

Engine::Engine(ScreenMode wMode, unsigned int width = 0, unsigned int height = 0):
	mWindowMode{ wMode }, mScnWidht{ sf::VideoMode::getDesktopMode().width / 2 }, mScnHeight{ sf::VideoMode::getDesktopMode().height / 2 }, mWorking{true}
{
}


void Engine::Run()
{
	Log(ERROR) << "Engine has been started" << 1 << 2 << 3;
	
	mMainThread = std::make_unique<std::thread>(std::thread([&]() {
		mWindow.create(sf::VideoMode(mScnWidht, mScnHeight), WINDOW_NAME, mWindowMode);
		while (mWindow.isOpen() && mWorking == true)
		{
			while (mWindow.pollEvent(mEvent))
			{
				if (mEvent.type == sf::Event::Closed || mWorking == false)
					mWindow.close();
			}
			mWindow.display();
		}
		mWindow.close();
	}));
}

Engine::~Engine()
{
	mMainThread->join();
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
	mWorking = false;
}
