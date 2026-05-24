#include "Core/Engine.hpp"
#include "Util/Log.hpp"
#include "EntityComponents/ComponentLinker.hpp"

namespace Oblivion
{
	Engine::Engine() :
		mWorking{ true }, mLastRenderTime{ 1 }, mCurrentScene(std::make_unique<Scene>(this)), mIsSceneRunning{ false }, mRenderTarget{nullptr}
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

		sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920, 1080), WINDOW_NAME, sf::Style::Resize | sf::Style::Close);

		mRenderTarget = &window;

		while (window.isOpen() && mWorking == true)
		{
			while (window.pollEvent(mEvent))
			{
				if (mEvent.type == sf::Event::Closed || mWorking == false)
					window.close();
			}
			
			Update(mRenderTarget);

			window.display();
		}
		window.close();
	}

	void Engine::Tick(float time)
	{

	}

	void Engine::Update(sf::RenderTarget* window)
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
	}

	void Engine::SetRenderTarget(sf::RenderTarget* target)
	{
		mRenderTarget = target;
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
	}

	sf::RenderTarget* Engine::GetRenderWindow()
	{
		return mRenderTarget;
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