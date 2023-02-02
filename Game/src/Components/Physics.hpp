#ifndef PHYSICS_H
#define PHYSICS_H

#include "IComponent.hpp"
#include "box2d.h"
#include "../Util/Util.hpp"

enum class PhysicsObjectType
{
	CHAIN,
	CIRCLE,
	EDGE,
	POLYGON
};

class PhysicsComponent : public IComponent
{
public:
	PhysicsComponent() = delete;
	PhysicsComponent(b2World*, const PhysicsObjectType&, b2BodyDef&, Vec2 size = Vec2(30.f, 30.f), Vec2 pos = Vec2(), float density = 1.f);
	~PhysicsComponent() override;
	void Update() override;
	Vec2 GetSize() const;
	Vec2 GetPosition() const;
	const char* GetName() override;
private:
	b2Body* mBody;
	Vec2 mSize;
};

#endif // !PHYSICS_H
