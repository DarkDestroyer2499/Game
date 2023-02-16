#include "Physics.hpp"
#include "../Entity.hpp"
#include "../Util/Util.hpp"

//TODO: Add more object type to constructor switch

PhysicsComponent::PhysicsComponent(b2World* world, const PhysicsObjectType& type, b2BodyDef& bdef, Vec2 size, Vec2 pos, float density)
	: mSize{size}
{
	this->mBody = world->CreateBody(&bdef);
	
	switch (type)
	{
	case PhysicsObjectType::POLYGON:
	{
		b2PolygonShape shape;
		shape.SetAsBox(size.x /2, size.y/2);
		
		this->mBody->CreateFixture(&shape, density);
		this->mBody->SetTransform(b2Vec2((float)pos.x, (float)pos.y), 0);
		break;
	}
	}
	mName = COMPONENT_NAME;
}

PhysicsComponent::PhysicsComponent(b2World* world, const PhysicsObjectType& type, b2BodyDef& bdef, b2FixtureDef fdef, Vec2 size, Vec2 pos, float density)
	: mSize{ size }
{
	this->mBody = world->CreateBody(&bdef);

	switch (type)
	{
	case PhysicsObjectType::POLYGON:
	{
		b2PolygonShape shape;
		shape.SetAsBox(size.x / 2, size.y / 2);

		this->mBody->CreateFixture(&fdef);
		this->mBody->SetTransform(b2Vec2((float)pos.x, (float)pos.y), 0);
		break;
	}
	}
	mName = COMPONENT_NAME;
}

PhysicsComponent::~PhysicsComponent()
{
	mBody->GetWorld()->DestroyBody(mBody);
}


void PhysicsComponent::Update(const float& ts)
{
	b2Vec2 pos = mBody->GetPosition();
	mOwner->SetPosition(Vec2(pos.x, pos.y) );
	mOwner->SetRotation(mBody->GetAngle());
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