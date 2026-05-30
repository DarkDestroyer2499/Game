#include "Graphics.hpp"
#include "Core/Entity.hpp"
#include "Core/Engine.hpp"
#include "Core/ResourceComponents/ResourceComponentLinker.hpp"

namespace Oblivion
{
	GraphicsComponent::GraphicsComponent()
	{
	}

	GraphicsComponent::GraphicsComponent(const sf::Texture& texture, const sf::IntRect& rect)
	{
		mSprite.setTexture(texture);
		mSprite.setTextureRect(rect);
		mSprite.setOrigin(float(rect.width / 2), float(rect.height / 2));
	}

	GraphicsComponent::GraphicsComponent(sf::Sprite sprite) : mSprite{ ::std::move(sprite) }
	{
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

	void GraphicsComponent::Update(float time)
	{
		
		mSprite.setPosition(mOwner->GetTransform()->position.x, mOwner->GetTransform()->position.y);
		mSprite.setRotation(mOwner->GetTransform()->rotation * 57.2957795f);
	}
	void GraphicsComponent::Render(sf::RenderTarget* target)
	{
		if (mSprite.getTexture() == nullptr)
			return;

		target->draw(mSprite);
	}
	sf::Sprite& GraphicsComponent::GetSprite()
	{
		return mSprite;
	}
}
