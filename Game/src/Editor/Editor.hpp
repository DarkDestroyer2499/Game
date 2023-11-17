#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "Core/Engine.hpp"
#include "Util/Util.hpp"
#include "UIVisualSelector.h"
#include "Components/EditorComponents.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Core/ECS.hpp"

namespace Oblivion
{
	constexpr const char* PROGRAM_NAME = "Engine";
	static const sf::Color EDITOR_BG_COLOR(62, 66, 63);

	class Editor : public EventSubscriber
	{
	public:
		Editor(sf::RenderTexture*, Engine&);
		Editor(Editor&&) = delete;
		Editor(Editor&) = delete;
		~Editor();

		Vec2 WindowToViewportCoords(const Vec2& windowCoords);
		void Run();
		Engine* GetEngine();
		sf::RenderTexture* GetRenderTexture();
		Vec2 GetMousePosition();
		sf::RenderWindow& GetMainWindow();

		template<typename Component>
		bool HasComponent()
		{
			return ecs.GetComponent<Component>();
		}

		template<typename Component>
		Component* GetComponent()
		{
			return ecs.GetComponent<Component>();
		}

		template<typename Component, typename... Args>
		Component* AddComponent(Args&&... args)
		{
			return ecs.AddComponent<Component>(args...);
		}

		template<typename Component>
		void RemoveComponent()
		{
			ecs.RemoveComponent<Component>();
		}

		::std::vector<IEditorComponent*>& GetComponentList()
		{
			return this->ecs.GetComponentList();
		}

	private:
		void OnWindowClosed() override;
		void OnResized(const sf::Event&) override;

		void SetupStyles();

	public:
		ECS<IEditorComponent, Editor*> ecs;

	private:
		sf::RenderWindow mWindow;
		sf::Clock mClock;
		sf::Event mEvent;
		sf::RenderTexture* mTexture;
		Engine& mEngine;
		sf::Vector2i mMousePosition;
		sf::View mView;
	};
}
#endif // !EDITOR_H
