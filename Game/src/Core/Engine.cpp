#include "Core/Engine.hpp"
#include "Util/Log.hpp"
#include "EntityComponents/ComponentLinker.hpp"

namespace Oblivion
{
	Engine::Engine() :
		mWorking{ true }, mLastRenderTime{ 1 }, mCurrentScene(std::make_unique<Scene>(this)), mIsSceneRunning{ false }
	{
		mWorld = ::std::make_unique<b2World>(b2Vec2(0.f, 9.8f));
		eventBroadcaster.Attach(EventType::OnAnyEntityCreated, this);
		eventBroadcaster.Attach(EventType::OnAnyEntityRemoved, this);

		resourceManager.resources.AddComponent<TextureComponent>();
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

	void Engine::RunStandalone()
	{
		Log(SUCCESS, "Engine has been started");

		sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920, 1080), WINDOW_NAME, ScreenMode::Resize);

		while (window.isOpen() && mWorking == true)
		{
			while (window.pollEvent(mEvent))
			{
				if (mEvent.type == sf::Event::Closed || mWorking == false)
					window.close();
			}
			//Draw sprite of all objects
			window.clear();

			float deltaTime = mClock.restart().asSeconds();
			mLastRenderTime = (uint32_t)(deltaTime * 1000000.f);

			for (auto& object : mCurrentScene->GetEntityList())
			{
				object.Update(deltaTime);
			}

			mWorld->Step(1 / 500.f, 8, 3);

			window.display();
		}
		window.close();
	}

	void Engine::Tick(float time)
	{

	}

	void Engine::Update(sf::RenderTexture* window)
	{
		static const sf::Color gbColor(62, 66, 63);

		window->clear(gbColor);

		float deltaTime = mClock.restart().asSeconds();
		mLastRenderTime = (uint32_t)(deltaTime * 1000000.f);

		float time = 0;
		if (mIsSceneRunning)
		{
			mWorld->Step(1.f / 400.f, 8, 3);
			time = deltaTime;
		}

		for (auto& object : mCurrentScene->GetEntityList())
		{
			object.Update(time);
		}

		window->display();
	}

	void Engine::SetCurrentSceneState(bool newState)
	{
		mIsSceneRunning = newState;
	}

	bool Engine::GetCurrentSceneState()
	{
		return mIsSceneRunning;
	}

	Engine::~Engine()
	{
		Stop();
		if (mMainThread != nullptr && mMainThread->joinable())
			mMainThread->join();
	}

	sf::RenderTarget* Engine::GetRenderWindow()
	{
		auto tmpWindow = dynamic_cast<sf::RenderWindow*>(mRenderTarget);
		if (!tmpWindow)
		{
			return static_cast<sf::RenderTexture*>(mRenderTarget);
		}
		else
		{
			return static_cast<sf::RenderWindow*>(mRenderTarget);
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