#ifndef PHYSICS_HPP
#define PHYSICS_HPP

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
		PhysicsComponent(b2World*, const PhysicsObjectType&, b2BodyDef, b2FixtureDef fdef, Vec2 size = Vec2(30.f, 30.f), Vec2 pos = Vec2(), float density = 1.f);
		~PhysicsComponent() override;

		::std::unique_ptr<IEntityComponent> Clone() const override;
		void Update(const float&) override;
		Vec2 GetSize() const;
		void SetPosition(Vec2 newPosition);
		Vec2 GetPosition() const;
		void SetRotation(float newRotation);
		float GetRotation() const;
		b2Body* GetBody() { return mBody; }
		PhysicsObjectType GetPhysicsType();
		b2BodyDef GetBodyDef();
		float GetDensity();
		b2FixtureDef GetFixtureDef();
	private:
		PhysicsObjectType mType;
		b2Body* mBody;
		Vec2 mSize;
		b2BodyDef mBodyDef;
		float mDensity;
		b2FixtureDef mFixtureDef;
	};
}
#endif // !PHYSICS_HPP
