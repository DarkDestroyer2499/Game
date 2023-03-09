#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "Components/ComponentLinker.hpp"
#include "Util/Util.hpp"
#include "Util/Log.hpp"
#include "Core/ECS.hpp"

namespace Oblivion
{
	class Engine;

	class Entity
	{
	public:
		Entity() = default;
		Entity(Engine* engine, const char* newName = "Unknown");
		Entity(const Entity& other) { Log(ERROR, "Entity has been copied!"); };
		virtual ~Entity();

		virtual void Update(const float&);
		void SetPosition(const Vec2&);
		Vec2 GetPosition() const;
		Vec2 GetSize();
		void SetRotation(float);
		float GetRotation() const;
		Engine* GetEngine();

	public:
		ECS<IEntityComponent, Entity*> ecs;

	protected:
		Engine* mEngine;
		Vec2 mPosition;
		Vec2 mSize;
		float mRotation;
	};
}
#endif // !ENTITY_H
