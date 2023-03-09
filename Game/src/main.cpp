#include <SFML/Graphics.hpp>
#include "Core/Engine.hpp" 
#include <Windows.h>
#include "Editor/Editor.hpp"
#include "Core/Entity.hpp"
#include <thread>
#include "Editor/Components/EditorComponents.hpp"

using namespace sf;

using namespace Oblivion;

int main()
{
	sf::RenderTexture window;

	Engine engine(&window, ScreenMode::Close, 0, 0);
	Editor editor(&window, engine);
	engine.Run();

	editor.ecs.AddComponent<ViewportComponent>(&editor);
	editor.ecs.AddComponent<HierarchyComponent>(&editor);
	editor.ecs.AddComponent<MenuBarComponent>(&editor);
	editor.ecs.AddComponent<PropertiesComponent>(&editor);
	editor.ecs.AddComponent<FileExplorerComponent>(&editor);
	editor.ecs.AddComponent<SelectionHandlerComponent>(&editor, &engine);

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
	ent5->ecs.AddComponent<AnimatedGraphicsComponent>();
	ent5->ecs.AddComponent<PhysicsComponent>(engine.GetMainWorld(), PhysicsObjectType::POLYGON, bdef, Vec2(50, 50), Vec2(190, 0));
	auto* anim = ent5->ecs.GetComponent<AnimatedGraphicsComponent>();

	sf::Texture playerTexture;
	playerTexture.loadFromFile("../resources/fang.png");

	anim->AddAnimation("walk", playerTexture, Vec2(0, 244), Vec2(40, 50), 6, 2, 40);
	anim->AddAnimation("jump", playerTexture, Vec2(0, 528), Vec2(29, 30), 4, 2, 38);
	anim->AddAnimation("duck", playerTexture, Vec2(0, 436), Vec2(80, 20), 1, 2, 38);
	anim->AddAnimation("stay", playerTexture, Vec2(0, 187), Vec2(42, 52), 3, 2, 42);
	anim->AddAnimation("shoot", playerTexture, Vec2(0, 572), Vec2(45, 52), 5, 2, 45.5f);


	anim->Set("walk");

	Entity* ent1 = engine.CreateObject("Ama bird!");


	ent1->ecs.AddComponent<PhysicsComponent>(engine.GetMainWorld(), PhysicsObjectType::POLYGON, bdef, Vec2(50, 50), Vec2(190, 80));
	ent1->ecs.AddComponent<GraphicsComponent>(sprite);
	
	
	Entity* ent3 = engine.CreateObject("Ama floor!");
	sprite.setTextureRect(sf::IntRect(50, 50, 200, 30));
	ent3->ecs.AddComponent<GraphicsComponent>(sprite);
	b2BodyDef bdef2;
	ent3->ecs.AddComponent<PhysicsComponent>(engine.GetMainWorld(), PhysicsObjectType::POLYGON, bdef2, Vec2(200, 30), Vec2(100, 400));
	//ent3->RemoveComponent<PhysicsComponent>();
	editor.Run();
	
	return 0;
}
