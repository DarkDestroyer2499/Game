#include "Engine.hpp"
#include "Log.h"
#include "Components/ComponentLinker.hpp"

Engine::Engine(ScreenMode wMode, unsigned int width = 0, unsigned int height = 0):
	mWindowMode{ wMode }, mScnWidht{ sf::VideoMode::getDesktopMode().width / 2 }, mScnHeight{ sf::VideoMode::getDesktopMode().height / 2 }, mWorking{true}
{
	mWorld = std::make_unique<b2World>(GRAVITY);
}

void Engine::Run()
{
	Log(SUCCESS) << "Engine has been started" << 1 << 2 << 3;
	
	mMainThread = std::make_unique<std::thread>(std::thread([this]() {
		Update();
	}));
}

void Engine::Update()
{
	mWindow.create(sf::VideoMode(mScnWidht, mScnHeight), WINDOW_NAME, mWindowMode);
	while (mWindow.isOpen() && mWorking == true)
	{
		while (mWindow.pollEvent(mEvent))
		{
			if (mEvent.type == sf::Event::Closed || mWorking == false)
				mWindow.close();
		}
		//Draw sprite of all objects
		mWindow.clear();

		for (auto& object : mObjectList)
		{
			object.Update();
			//mWindow.draw(object.GetSprite());
		}

		mWorld->Step(1 / 500.f, 8, 3);

		mWindow.display();
	}
	mWindow.close();
}

Engine::~Engine()
{
	Stop();
	if(mMainThread->joinable())
		mMainThread->join();
}

sf::RenderWindow& Engine::GetWindow()
{
	return mWindow;
}

b2World* Engine::GetMainWorld()
{
	return mWorld.get();
}

void Engine::SetScreenMode(ScreenMode newMode)
{
	mWindow.create(sf::VideoMode(mScnWidht, mScnHeight), WINDOW_NAME, newMode);
}

Entity& Engine::CreateObject()
{
	mObjectList.push_back( Entity(static_cast<sf::RenderTarget*>(&mWindow)));
	return mObjectList[mObjectList.size() - 1];
}

void Engine::Stop()
{
	mWorking = false;
}
