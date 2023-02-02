#include "Graphics.hpp"
#include "../Entity.hpp"

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
	sf::IntRect tmpRect = sprite.getTextureRect();
	mSprite.setOrigin(float(tmpRect.width / 2), float(tmpRect.height / 2));
}

GraphicsComponent::~GraphicsComponent()
{
}

void GraphicsComponent::Update() 
{
	mSprite.setPosition(mOwner->GetPosition().x, mOwner->GetPosition().y);
	mSprite.setRotation(mOwner->GetRotation() * 57.2957795f);
	mOwner->GetWindow()->draw(mSprite);
}

const char* GraphicsComponent::GetName()
{
	return mName.c_str();
}
