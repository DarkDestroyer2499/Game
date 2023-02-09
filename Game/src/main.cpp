#include <SFML/Graphics.hpp>
#include "Engine.hpp" 
#include <Windows.h>
#include "EngineUI/Editor.hpp"
#include "Entity.hpp"
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
	sprite.setTextureRect(sf::IntRect(50, 50, 50, 50));



	b2BodyDef bdef;
	bdef.type = b2_dynamicBody;
	Entity* ent5 = engine.CreateObject("Big image");

	sf::Texture t1;
	t1.loadFromFile("../resources/1.jpg");
	sf::Sprite s1(t1);
	s1.setTextureRect(sf::IntRect(20, 20, 50, 50));

	
	//ent5->AddComponent<GraphicsComponent>(new GraphicsComponent(s1));
	ent5->AddComponent<AnimatedGraphicsComponent>();
	ent5->AddComponent<PhysicsComponent>(engine.GetMainWorld(), PhysicsObjectType::POLYGON, bdef, Vec2(50, 50), Vec2(190, 0));
	auto* anim = ent5->GetComponent<AnimatedGraphicsComponent>();

	sf::Texture playerTexture;
	playerTexture.loadFromFile("../resources/fang.png");

	anim->AddAnimation("walk", playerTexture, Vec2(0, 244), Vec2(40, 50), 6, 2, 40);
	anim->AddAnimation("jump", playerTexture, Vec2(0, 528), Vec2(29, 30), 4, 2, 38);
	anim->AddAnimation("duck", playerTexture, Vec2(0, 436), Vec2(80, 20), 1, 2, 38);
	anim->AddAnimation("stay", playerTexture, Vec2(0, 187), Vec2(42, 52), 3, 2, 42);
	anim->AddAnimation("shoot", playerTexture, Vec2(0, 572), Vec2(45, 52), 5, 2, 45.5f);


	anim->Set("wal");

	Entity* ent1 = engine.CreateObject("Ama bird!");


	ent1->AddComponent<PhysicsComponent>(engine.GetMainWorld(), PhysicsObjectType::POLYGON, bdef, Vec2(50, 50), Vec2(210, 80));
	ent1->AddComponent<GraphicsComponent>(sprite);
	
	
	Entity* ent3 = engine.CreateObject("Ama floor!");
	sprite.setTextureRect(sf::IntRect(50, 50, 200, 30));
	ent3->AddComponent<GraphicsComponent>(sprite);
	b2BodyDef bdef2;
	ent3->AddComponent<PhysicsComponent>(engine.GetMainWorld(), PhysicsObjectType::POLYGON, bdef2, Vec2(200, 30), Vec2(100, 400));
	//ent3->RemoveComponent<PhysicsComponent>();
	editor.Run();
	
	system("pause");
	return 0;
}
