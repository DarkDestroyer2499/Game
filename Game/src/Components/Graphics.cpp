#include "Graphics.hpp"
#include "../Entity.hpp"


GraphicsComponent::GraphicsComponent(sf::Texture& texture, const sf::IntRect& rect)
{
	mSprite.setTexture(texture);
	mSprite.setTextureRect(rect);
	mSprite.setOrigin(float(rect.width / 2), float(rect.height / 2));
}

GraphicsComponent::GraphicsComponent(sf::Sprite sprite) : mSprite{std::move(sprite)}
{
}

void GraphicsComponent::Update() 
{
	mSprite.setPosition(mOwner->GetPosition().x, mOwner->GetPosition().y);
	mOwner->GetWindow()->draw(mSprite);
}

GraphicsComponent::~GraphicsComponent()
{
}

