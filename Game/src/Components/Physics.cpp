#include "Physics.hpp"
#include "../Entity.hpp"
#include "../Util.hpp"

//TODO: Add more object type to constructor switch

PhysicsComponent::PhysicsComponent(b2World* world, const PhysicsObjectType& type, b2BodyDef& bdef, Vec2 size, float density)
	: mSize{size}
{
	this->mBody = world->CreateBody(&bdef);

	switch (type)
	{
	case PhysicsObjectType::POLYGON:
	{
		b2PolygonShape shape;
		shape.SetAsBox(size.x / SCALE, size.y / SCALE);
		this->mBody->CreateFixture(&shape, density);
		break;
	}
	}
	
	mName = COMPONENT_NAME;
}

void PhysicsComponent::Update()
{
	mOwner->SetPosition(mBody->GetPosition());
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
