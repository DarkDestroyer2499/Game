#include "Core/Engine.hpp"
#include "Util/Log.hpp"
#include "EntityComponents/ComponentLinker.hpp"

namespace Oblivion
{
	Engine::Engine(sf::RenderTarget* window, ScreenMode wMode, unsigned int width = 0, unsigned int height = 0) :
		mWindow{ window }, mWindowMode{ wMode }, mScnWidht{ sf::VideoMode::getDesktopMode().width / 2 },
		mScnHeight{ sf::VideoMode::getDesktopMode().height / 2 }, mWorking{ true }, mLastRenderTime{ 1 }, mCurrentScene(std::make_unique<Scene>(this))
	{
		mWorld = ::std::make_unique<b2World>(b2Vec2(0.f, 9.8f));
		eventBroadcaster.Attach(EventType::OnAnyEntityCreated, this);
		eventBroadcaster.Attach(EventType::OnAnyEntityRemoved, this);
	}

	Entity* Engine::GetEntityByID(UUID uuid)
	{
		for (auto& entity : mCurrentScene->GetEntityList())
		{
			if (entity.GetUUID() == uuid)
				return &entity;
		}

		return nullptr;
	}

	void Engine::Run()
	{
		Log(SUCCESS, "Engine has been started");

		auto tmpWindow = dynamic_cast<sf::RenderWindow*>(mWindow);
		if (!tmpWindow)
		{
			Log(WARNING, "External texture will be rendered!");
		}
		else
		{
			Log(WARNING, "Engine runned in window mode!");
			mMainThread = ::std::make_unique<::std::thread>(::std::thread([this]() {
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

			for (auto& object : mCurrentScene->GetEntityList())
			{
				object.Update(1.f / (float)mLastRenderTime);
			}

			mWorld->Step(1 / 500.f, 8, 3);

			window->display();
			mLastRenderTime = (uint32_t)mClock.getElapsedTime().asMicroseconds();
			mClock.restart();
		}
		window->close();
	}

	void Engine::Update(sf::RenderTexture* window)
	{
		static const sf::Color gbColor(62, 66, 63); 

		window->clear(gbColor);

		for (auto& object : mCurrentScene->GetEntityList())
		{
			object.Update(1.f / (float)mLastRenderTime);
		}

		mWorld->Step(1.f / 400.f, 8, 3);

		window->display();

		mLastRenderTime = (uint32_t)mClock.getElapsedTime().asMicroseconds();
		mClock.restart();
	}

	Engine::~Engine()
	{
		Stop();
		if (mMainThread != nullptr && mMainThread->joinable())
			mMainThread->join();
	}

	sf::RenderTarget* Engine::GetRenderWindow()
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

	uint32_t Engine::GetRenderTime()
	{
		return mLastRenderTime;
	}

	Scene* Engine::GetCurrentScene()
	{
		return mCurrentScene.get();
	}

	void Engine::SetCurrentScene(std::unique_ptr<Scene> newScene)
	{
		mCurrentScene = std::move(newScene);
	}

	void Engine::SetScreenMode(ScreenMode newMode)
	{
		//mWindow.create(sf::VideoMode(mScnWidht, mScnHeight), WINDOW_NAME, newMode);
	}

	Entity* Engine::CreateObject(::std::string name)
	{
		::std::list<Entity>& entityList = mCurrentScene->GetEntityList();
		Entity& entity = entityList.emplace_back(this, name.c_str());
		Log(INFO, entity.GetUUID() << " Create entity with name: " << name);
		eventBroadcaster.Notify(EventType::OnAnyEntityCreated, &entity);
		return &entity;
	}

	Entity* Engine::CreateObject(Scene& scene, ::std::string name)
	{
		::std::list<Entity>& entityList = scene.GetEntityList();
		entityList.emplace_back(this, name.c_str());
		Log(INFO, entityList.back().GetUUID() << " Create entity with name: " << name);
		return &entityList.back();
	}

	Entity* Engine::CloneObject(Entity* entity)
	{
		std::string name = entity->GetComponent<TagComponent>()->GetTag();
		Entity* cloneEnt = CreateObject(name);
		
		cloneEnt->GetEcs().GetComponentList().clear();

		cloneEnt->LoadEcs(entity->GetEcs());

		for (auto& component : cloneEnt->GetComponentList())
		{
			component->SetOwner(cloneEnt);
		}

		return cloneEnt;
	}

	void Engine::RemoveObject(Entity* entity)
	{
		UUID entId = entity->GetUUID();
		auto& entityList = mCurrentScene.get()->GetEntityList();
		auto it = entityList.begin();
		while (it != entityList.end())
		{
			if (it->GetUUID() == entId)
			{
				eventBroadcaster.Notify(EventType::OnAnyEntityRemoved, &(*it));
				entityList.erase(it);
				return;
			}
			it++;
		}
		Log(ERROR, "Attempted to remove entity with non registered id!");
	}

	void Engine::Stop()
	{
		mWorking = false;
	}
}