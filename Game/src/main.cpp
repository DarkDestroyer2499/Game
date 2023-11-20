#include <SFML/Graphics.hpp>
#include "Core/Engine.hpp" 
#include <Windows.h>
#include "Editor/Editor.hpp"
#include "Core/Entity.hpp"
#include <thread>
#include "Editor/Components/EditorComponents.hpp"
#include "Core/ResourceComponents/ResourceComponentLinker.hpp"

using namespace sf;

using namespace Oblivion;

int main()
{
	sf::RenderTexture window;

	Engine engine(&window, ScreenMode::Close, 0, 0);
	Editor editor(&window, engine);
	engine.Run();

	engine.resourceManager.resources.AddComponent<TextureComponent>();
	editor.AddComponent<ViewportComponent>(&editor);
	editor.AddComponent<CameraComponent>(&editor);

	
	editor.AddComponent<HierarchyComponent>(&editor);
	editor.AddComponent<MenuBarComponent>(&editor);
	editor.AddComponent<PropertiesComponent>(&editor);
	editor.AddComponent<FileExplorerComponent>(&editor);
	editor.AddComponent<SelectionHandlerComponent>(&editor, &engine);
	editor.AddComponent<ToolbarComponent>(&editor);

	auto textureComponent = engine.resourceManager.resources.GetComponent<TextureComponent>();
	textureComponent->SetOwner(&engine.resourceManager);

	

	sf::Sprite sprite(*textureComponent->AddTexture("../resources/TestSprite.jpg"));
	
	sprite.setTextureRect(sf::IntRect(50, 50, 50, 50));

	b2BodyDef bdef;
	bdef.type = b2_dynamicBody;
	Entity* ent5 = engine.CreateObject("Big image");

	ent5->rm->resources.GetComponent<TextureComponent>();

	sf::Sprite s1(*textureComponent->AddTexture("../resources/1.jpg"));
	s1.setTextureRect(sf::IntRect(20, 20, 50, 50));

	
	ent5->AddComponent<GraphicsComponent>();
	auto* anim = ent5->AddComponent<AnimatedGraphicsComponent>();
	ent5->AddComponent<PhysicsComponent>(engine.GetMainWorld(), PhysicsObjectType::POLYGON, bdef, Vec2(50, 50), Vec2(190, 0));

	sf::Texture* playerTexture = textureComponent->AddTexture("../resources/fang.png");

	anim->AddAnimation("walk", *playerTexture, Vec2(0, 244), Vec2(40, 50), 6, 2, 40);
	anim->AddAnimation("jump", *playerTexture, Vec2(0, 528), Vec2(29, 30), 4, 2, 38);
	anim->AddAnimation("duck", *playerTexture, Vec2(0, 436), Vec2(80, 20), 1, 2, 38);
	anim->AddAnimation("stay", *playerTexture, Vec2(0, 187), Vec2(42, 52), 3, 2, 42);
	anim->AddAnimation("shoot", *playerTexture, Vec2(0, 572), Vec2(45, 52), 5, 2, 45.5f);


	anim->Set("walk");


	Entity* ent1 = engine.CreateObject("Ama bird!");


	ent1->AddComponent<PhysicsComponent>(engine.GetMainWorld(), PhysicsObjectType::POLYGON, bdef, Vec2(50, 50), Vec2(190, 80));
	ent1->AddComponent<GraphicsComponent>(sprite);
	
	
	Entity* ent3 = engine.CreateObject("Ama floor!");
	sprite.setTextureRect(sf::IntRect(50, 50, 200, 30));
	ent3->AddComponent<GraphicsComponent>(sprite);
	b2BodyDef bdef2;
	ent3->AddComponent<PhysicsComponent>(engine.GetMainWorld(), PhysicsObjectType::POLYGON, bdef2, Vec2(200, 30), Vec2(100, 400));
	//ent3->RemoveComponent<PhysicsComponent>();
	editor.Run();
	
	return 0;
}
