#ifndef PHYSICS_H
#define PHYSICS_H

#include "IEntityComponent.hpp"
#include "box2d.h"
#include "Util/Util.hpp"

namespace Oblivion
{
	enum class PhysicsObjectType
	{
		CHAIN,
		CIRCLE,
		EDGE,
		POLYGON
	};

	class PhysicsComponent : public IEntityComponent
	{
	public:
		PhysicsComponent() = delete;
		PhysicsComponent(b2World*, const PhysicsObjectType&, b2BodyDef&, Vec2 size = Vec2(30.f, 30.f), Vec2 pos = Vec2(), float density = 1.f);
		PhysicsComponent(b2World*, const PhysicsObjectType&, b2BodyDef&, b2FixtureDef fdef, Vec2 size = Vec2(30.f, 30.f), Vec2 pos = Vec2(), float density = 1.f);
		~PhysicsComponent() override;

		void Update(const float&) override;
		Vec2 GetSize() const;
		void SetPosition(Vec2 newPosition);
		Vec2 GetPosition() const;
		void SetRotation(float newRotation);
		float GetRotation() const;
		b2Body* GetBody() { return mBody; }
	private:
		b2Body* mBody;
		Vec2 mSize;
	};
}
#endif // !PHYSICS_H
