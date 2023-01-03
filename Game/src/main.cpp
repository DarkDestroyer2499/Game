#include <SFML/Graphics.hpp>
#include "Engine.hpp" 
#include <Windows.h>
#include "Editor.hpp"
#include <thread>
using namespace sf;

int main()
{
	sf::RenderTexture window;


	Engine engine(&window, ScreenMode::Close, 0, 0);
	Editor editor(&window, engine);
	engine.Run();

	sf::Texture t;

	t.loadFromFile("../resources/TestSprite.jpg");

	sf::Sprite sprite(t);
	sprite.setTextureRect(sf::IntRect(50, 50, 100, 100));

	b2PolygonShape shape;
	shape.SetAsBox(30 / SCALE, 30 / SCALE);

	b2BodyDef bdef;
	bdef.type = b2_dynamicBody;

	Entity* ent1 = engine.CreateObject("Ama bird!");

	ent1->AddComponent<GraphicsComponent>(new GraphicsComponent(sprite));
	ent1->AddComponent<PhysicsComponent>(new PhysicsComponent(engine.GetMainWorld(), shape, bdef));
	
	Entity* ent2 = engine.CreateObject("Ama dog!");
	ent2->AddComponent<GraphicsComponent>(new GraphicsComponent(sprite));
	editor.Run();
	
	system("pause");
	return 0;
}
