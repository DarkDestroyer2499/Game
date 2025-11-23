#include "Physics.hpp"
#include "Core/Entity.hpp"
#include "Util/Util.hpp"

//TODO: Add more object type to constructor switch

namespace Oblivion
{

	PhysicsComponent::PhysicsComponent(b2World* world, const PhysicsObjectType& type, b2BodyDef& bdef, Vec2 size, Vec2 pos, float density)
		: mSize{ size }, mType{ type }, mBodyDef{ bdef }, mDensity{ density }
	{
		this->mBody = world->CreateBody(&bdef);

		switch (type)
		{
		case PhysicsObjectType::POLYGON:
		{
			b2PolygonShape shape;
			shape.SetAsBox(size.x / 2, size.y / 2);

			this->mBody->CreateFixture(&shape, density);
			this->mBody->SetTransform(b2Vec2((float)pos.x, (float)pos.y), 0);
			break;
		}
		}
		mName = COMPONENT_NAME;
	}

	::std::unique_ptr<IEntityComponent> PhysicsComponent::Clone() const
	{
		return ::std::make_unique<PhysicsComponent>(mBody->GetWorld(), mType, mBodyDef, mFixtureDef, mSize, mBody->GetPosition(), mDensity);
	}

	PhysicsComponent::PhysicsComponent(b2World* world, const PhysicsObjectType& type, b2BodyDef bdef, b2FixtureDef fdef, Vec2 size, Vec2 pos, float density)
		: mSize{ size }, mType{ type }, mBodyDef{ bdef }, mDensity{ density }, mFixtureDef{ fdef }
	{
		this->mBody = world->CreateBody(&bdef);

		switch (type)
		{
		case PhysicsObjectType::POLYGON:
		{
			b2PolygonShape shape;
			shape.SetAsBox(size.x / 2, size.y / 2);

			this->mBody->CreateFixture(&shape, density);

			this->mBody->SetTransform(b2Vec2(pos.x, pos.y), 0);

			break;
		}
		}
		mName = COMPONENT_NAME;
	}

	PhysicsComponent::~PhysicsComponent()
	{
		mBody->GetWorld()->DestroyBody(mBody);
	}

	void PhysicsComponent::Update(float ts)
	{
		b2Vec2 pos = mBody->GetPosition();
		mOwner->SetPosition(Vec2(pos.x, pos.y));
		mOwner->SetRotation(mBody->GetAngle());
	}

	void PhysicsComponent::Render(sf::RenderTarget* target)
	{
	}

	Vec2 PhysicsComponent::GetSize() const
	{
		return mSize;
	}

	Vec2 PhysicsComponent::GetPosition() const
	{
		b2Vec2 pos = mBody->GetPosition();
		return (Vec2(pos.x, pos.y));
	}

	void PhysicsComponent::SetPosition(Vec2 newPosition)
	{
		mBody->SetTransform({ newPosition.x, newPosition.y }, mBody->GetAngle());
	}

	void PhysicsComponent::SetRotation(float newRotation)
	{
		Vec2 position = mBody->GetPosition();
		mBody->SetTransform({ position.x, position.y }, newRotation);
	}

	float PhysicsComponent::GetRotation() const
	{
		return mBody->GetAngle();
	}
	PhysicsObjectType PhysicsComponent::GetPhysicsType()
	{
		return mType;
	}
	b2BodyDef PhysicsComponent::GetBodyDef()
	{
		return mBodyDef;
	}
	float PhysicsComponent::GetDensity()
	{
		return mDensity;
	}
	b2FixtureDef PhysicsComponent::GetFixtureDef()
	{
		return mFixtureDef;
	}
}