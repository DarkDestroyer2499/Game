#include "Graphics.hpp"
#include "Core/Entity.hpp"
#include "Core/Engine.hpp"
#include "Core/ResourceComponents/ResourceComponentLinker.hpp"

namespace Oblivion
{
	GraphicsComponent::GraphicsComponent()
	{
		mName = COMPONENT_NAME;
	}

	GraphicsComponent::GraphicsComponent(const sf::Texture& texture, const sf::IntRect& rect)
	{
		mSprite.setTexture(texture);
		mSprite.setTextureRect(rect);
		mSprite.setOrigin(float(rect.width / 2), float(rect.height / 2));
		mName = COMPONENT_NAME;
	}

	GraphicsComponent::GraphicsComponent(sf::Sprite sprite) : mSprite{ ::std::move(sprite) }
	{
		mName = COMPONENT_NAME;
		sf::IntRect tmpRect = sprite.getTextureRect();
		mSprite.setOrigin(float(tmpRect.width / 2), float(tmpRect.height / 2));
	}

	GraphicsComponent::GraphicsComponent(const GraphicsComponent& other)
		: mSprite{ other.mSprite }
	{
	}

	::std::unique_ptr<IEntityComponent> GraphicsComponent::Clone() const
	{
		return ::std::make_unique<GraphicsComponent>(*this);
	}

	void GraphicsComponent::Update(const float& time)
	{
		mSprite.setPosition(mOwner->GetPosition().x, mOwner->GetPosition().y);
		mSprite.setRotation(mOwner->GetRotation() * 57.2957795f);
		mOwner->GetEngine()->GetRenderWindow()->draw(mSprite);
	}
	sf::Sprite& GraphicsComponent::GetSprite()
	{
		return mSprite;
	}
}
