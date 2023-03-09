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

	class Editor
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

	public:
		ECS<IEditorComponent, Editor*> ecs;

	private:		
		void EventHandler();
		void KeyboardHandler();

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
