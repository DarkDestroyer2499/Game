#pragma once

#ifndef PHYSICS_H
#define PHYSICS_H

#include "IComponent.hpp"
#include "box2d.h"

class PhysicsComponent : public IComponent
{
public:
	PhysicsComponent() = delete;
	PhysicsComponent(b2World*, b2Shape& shape, b2BodyDef& bdef);
	void Update() override;
	const char* GetName() override;
	~PhysicsComponent() override;
private:
	b2Body* mBody;
};

#endif // !PHYSICS_H
