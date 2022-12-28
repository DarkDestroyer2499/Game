#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "Engine.hpp"

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
	sf::RenderWindow mWindow;
	sf::Clock mClock;
	sf::Event mEvent;
	sf::RenderTexture* mTexture;
	Engine& mEngine;
};

#endif // !EDITOR_H