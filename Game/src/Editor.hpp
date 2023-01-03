#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "UI.hpp"
constexpr const char* PROGRAM_NAME = "Engine";

class Editor
{
public:
	Editor(sf::RenderTexture*, Engine&);
	Editor(Editor&&) = delete;
	Editor(Editor&) = delete;
	~Editor();

	void Run();

private:
	bool IsAlreadySelected(Entity& entity);
	void EventHandler();

private:
	sf::RenderWindow mWindow;
	sf::Clock mClock;
	sf::Event mEvent;
	sf::RenderTexture* mTexture;
	Engine& mEngine;
	friend class UI;
	std::unique_ptr<UI> mUI;
	sf::Vector2i mMousePosition;
	std::vector<Entity*> mSelectedObjects;
};

#endif // !EDITOR_H
