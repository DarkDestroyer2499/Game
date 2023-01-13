#include "Engine.hpp"
#include "Log.hpp"
#include "Components/ComponentLinker.hpp"

Engine::Engine(sf::RenderTarget* window, ScreenMode wMode, unsigned int width = 0, unsigned int height = 0) :
	mWindow{ window }, mWindowMode{ wMode }, mScnWidht{ sf::VideoMode::getDesktopMode().width / 2 }, mScnHeight{ sf::VideoMode::getDesktopMode().height / 2 }, mWorking{ true }
{
	mWorld = std::make_unique<b2World>(GRAVITY);
	mObjectList.reserve(RESERVE_ENTITIES);
}

void Engine::Run()
{
	Log(SUCCESS, "Engine has been started");

	auto tmpWindow = dynamic_cast<sf::RenderWindow*>(mWindow);
	if (!tmpWindow)
	{
		Log(WARNING, "Texture will be rendered!");
	}
	else
	{
		Log(WARNING, "Window will be rendered!");
		mMainThread = std::make_unique<std::thread>(std::thread([this]() {
			Update(static_cast<sf::RenderWindow*>(mWindow));
		}));
	}
}

void Engine::Update(sf::RenderWindow* window)
{
	window->create(sf::VideoMode(mScnWidht, mScnHeight), WINDOW_NAME, mWindowMode);
	while (window->isOpen() && mWorking == true)
	{
		while (window->pollEvent(mEvent))
		{
			if (mEvent.type == sf::Event::Closed || mWorking == false)
				window->close();
		}
		//Draw sprite of all objects
		window->clear();

		for (auto& object : mObjectList)
		{
			object.Update();
		}

		mWorld->Step(1 / 500.f, 8, 3);

		window->display();
		mLastRenderTime = mClock.getElapsedTime().asMilliseconds();
		mClock.restart();
	}
	window->close();
}

void Engine::Update(sf::RenderTexture* window)
{	
	for (auto& object : mObjectList)
	{
		object.Update();
	}

	mWorld->Step(1 / 500.f, 8, 3);
	mLastRenderTime = mClock.getElapsedTime().asMilliseconds();
	mClock.restart();
}

Engine::~Engine()
{
	Stop();
	if (mMainThread != nullptr && mMainThread->joinable())
		mMainThread->join();
}

sf::RenderTarget* Engine::GetWindow()
{
	auto tmpWindow = dynamic_cast<sf::RenderWindow*>(mWindow);
	if (!tmpWindow)
	{
		return static_cast<sf::RenderTexture*>(mWindow);
	}
	else
	{
		return static_cast<sf::RenderWindow*>(mWindow);
	}
}

b2World* Engine::GetMainWorld()
{
	return mWorld.get();
}

float Engine::GetRenderTime()
{
	return mLastRenderTime;
}

void Engine::SetScreenMode(ScreenMode newMode)
{
	//mWindow.create(sf::VideoMode(mScnWidht, mScnHeight), WINDOW_NAME, newMode);
}

Entity* Engine::CreateObject(std::string name)
{
	Log(INFO, "Create entity with name: " << name);
	mObjectList.emplace_back( mWindow, name.c_str() );
	return &mObjectList[mObjectList.size() - 1];
}

void Engine::Stop()
{
	mWorking = false;
}
