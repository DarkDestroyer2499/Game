#include "Entity.hpp"

Entity::Entity(sf::Sprite& sprite):
	mSprite{sprite}
{
}

Entity::Entity(sf::Texture& t, const sf::IntRect& textureRect)
{
	mSprite.setTexture(t);
	mSprite.setTextureRect(textureRect);
	mSprite.setOrigin(float(textureRect.width / 2), float(textureRect.height / 2));
}

sf::Sprite& Entity::GetSprite()
{
	return mSprite;
}

Entity::~Entity()
{

}