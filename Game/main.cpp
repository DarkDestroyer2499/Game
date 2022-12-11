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

	b2PolygonShape shape;
	shape.SetAsBox(30 / SCALE, 30 / SCALE);

	b2BodyDef bdef;
	bdef.type = b2_dynamicBody;


	Entity &ent1 = engine.CreateObject(t, sf::IntRect(50, 50, 100, 100), shape, bdef);
	

	system("pause");
	return 0;
}