#include "Physics.hpp"
#include "../Entity.hpp"
#include "../Util.hpp"

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
		shape.SetAsBox(size.x / SCALE, size.y / SCALE, b2Vec2(5, 5), 0.f);
		
		this->mBody->CreateFixture(&shape, density);
		this->mBody->SetTransform(b2Vec2(pos.x, pos.y + mSize.y*2), this->mBody->GetAngle());
		break;
	}
	}
	mName = COMPONENT_NAME;
}

void PhysicsComponent::Update()
{
	b2Vec2 pos = mBody->GetPosition();
	mOwner->SetPosition(Vec2(pos.x, pos.y - mSize.y*2) );
}

Vec2 PhysicsComponent::GetSize() const
{
	return mSize;
}

Vec2 PhysicsComponent::GetPosition() const
{
	return mBody->GetPosition();
}

const char* PhysicsComponent::GetName()
{
	return mName.c_str();
}
PhysicsComponent::~PhysicsComponent()
{
}
