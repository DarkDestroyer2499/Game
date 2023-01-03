#include "Graphics.hpp"
#include "../Entity.hpp"

#include <iostream>
GraphicsComponent::GraphicsComponent(sf::Texture& texture, const sf::IntRect& rect)
{
	mSprite.setTexture(texture);
	mSprite.setTextureRect(rect);
	mSprite.setOrigin(float(rect.width / 2), float(rect.height / 2));
	mName = COMPONENT_NAME;
}

GraphicsComponent::GraphicsComponent(sf::Sprite sprite) : mSprite{std::move(sprite)}
{
	mName = COMPONENT_NAME;
}

void GraphicsComponent::Update() 
{
	mSprite.setPosition(mOwner->GetPosition().x, mOwner->GetPosition().y);
	mOwner->GetWindow()->draw(mSprite);
}

GraphicsComponent::~GraphicsComponent()
{
}

const char* GraphicsComponent::GetName()
{
	return mName.c_str();
}

