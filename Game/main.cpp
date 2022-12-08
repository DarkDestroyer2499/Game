#include <SFML/Graphics.hpp>
#include "src/Engine.hpp" 
#include <Windows.h>
using namespace sf;

int main()
{
	Engine engine(ScreenMode::Close, 0, 0);
	engine.Run();

	sf::Texture t;

	t.loadFromFile("resources/TestSprite.jpg");


	sf::Sprite sprite(t);
	sprite.setTextureRect(sf::IntRect(50, 50, 100, 100));

	Entity entity(sprite);
	entity.GetSprite().setPosition(300, 100);

	Entity &ent1 = engine.CreateObject(entity);
	Entity& ent2 = engine.CreateObject(entity);
	ent2.GetSprite().setPosition(400, 300);

	system("pause");
	return 0;
}