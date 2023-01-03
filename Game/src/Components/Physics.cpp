#include "Physics.hpp"
#include "../Entity.hpp"

PhysicsComponent::PhysicsComponent(b2World* world,b2Shape& shape, b2BodyDef& bdef)
{
	this->mBody = world->CreateBody(&bdef);
	this->mBody->CreateFixture(&shape, 2);
	mName = COMPONENT_NAME;
}

void PhysicsComponent::Update()
{
	mOwner->SetPosition(mBody->GetPosition());
}
const char* PhysicsComponent::GetName()
{
	return mName.c_str();
}
PhysicsComponent::~PhysicsComponent()
{
}
