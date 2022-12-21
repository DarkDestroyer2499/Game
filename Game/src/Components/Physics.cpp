#include "Physics.hpp"
#include "../Entity.hpp"

PhysicsComponent::PhysicsComponent(b2World* world,b2Shape& shape, b2BodyDef& bdef)
{
	this->mBody = world->CreateBody(&bdef);
	this->mBody->CreateFixture(&shape, 2);
}

void PhysicsComponent::Update()
{
	mOwner->SetPosition(mBody->GetPosition());
}

PhysicsComponent::~PhysicsComponent()
{
}
