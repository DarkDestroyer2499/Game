#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "Core/Entity.hpp"
#include "Scene.hpp"
#include "Core/ResourceManager.hpp"
#include <Core/EventSystem/EventBroadcaster.hpp>

namespace Oblivion
{

#define WINDOW_NAME "SUPER GAME"

	enum ScreenMode
	{
		None = 0,      ///< No border / title bar (this flag and all others are mutually exclusive)
		Titlebar = 1 << 0, ///< Title bar + fixed border
		Resize = 1 << 1, ///< Title bar + resizable border + maximize button
		Close = 1 << 2, ///< Title bar + close button
		Fullscreen = 1 << 3,
	};

	class Engine : public EventSubscriber
	{
	public:
		Engine();
		~Engine();

		Entity* GetEntityByID(UUID uuid);
		sf::RenderTarget* GetRenderWindow();
		Entity* CreateObject(::std::string name = ::std::string("Uknown"));
		Entity* CloneObject(Entity* entity);
		Entity* CreateObject(Scene& scene, ::std::string entityName = ::std::string("Uknown"));
		b2World* GetMainWorld();
		uint32_t GetRenderTime();
		Scene* GetCurrentScene();

		void RemoveObject(Entity*);

		void SetCurrentScene(std::unique_ptr<Scene> newScene);

		void RunStandalone();

		void Tick(float time);

		void Stop();
		void Update(sf::RenderTarget* window);

		void SetRenderTarget(sf::RenderTarget* target);

		void SetCurrentSceneState(bool state);
		bool GetCurrentSceneState();

	public:
		ResourceManager resourceManager;
		EventBroadcaster eventBroadcaster;

	private:
		sf::RenderTarget* mRenderTarget;
		bool mWorking, mIsSceneRunning;
		sf::Event mEvent;
		::std::unique_ptr<b2World> mWorld;
		std::unique_ptr<Scene> mCurrentScene;
		uint32_t mLastRenderTime;
		sf::Clock mClock;
	};
}
#endif // !ENGINE_H