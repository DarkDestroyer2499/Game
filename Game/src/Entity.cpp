#include "Entity.hpp"

Entity::Entity(sf::Texture& t, const sf::IntRect& textureRect)
{
	mSprite.setTexture(t);
	mSprite.setTextureRect(textureRect);
	mSprite.setOrigin(float(textureRect.width / 2), float(textureRect.height / 2));
}

void Entity::SetBody(b2Body* newBody)
{
	mBody = newBody;
}
b2Body* Entity::GetBody()
{
	return mBody;
}

sf::Sprite& Entity::GetSprite()
{
	return mSprite;
}

Entity::~Entity()
{

}