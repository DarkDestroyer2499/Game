#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "EntityComponents/ComponentLinker.hpp"
#include "Util/Util.hpp"
#include "Util/Log.hpp"
#include "Core/ECS.hpp"
#include "Core/ResourceComponents/ResourceComponentLinker.hpp"
#include "Core/UUID.hpp"

namespace Oblivion
{
	class Engine;

	class Entity
	{
	public:
		Entity();
		Entity(Engine* engine, const char* newName = "Unknown");
		Entity(const Entity& other);
		virtual ~Entity();

		virtual void Update(float);
		void SetPosition(const Vec2&);
		Vec2 GetPosition() const;
		Vec2 GetSize();
		void SetRotation(float);
		float GetRotation() const;
		Engine* GetEngine();

		void SetUUID(UUID);

		UUID GetUUID();

		template<typename Component>
		bool HasComponent()
		{
			return this->ecs.HasComponent<Component>();
		}

		template<typename Component>
		Component* GetComponent()
		{
			return ecs.GetComponent<Component>();
		}

		template<typename Component, typename... Args>
		Component* AddComponent(Args&&... args)
		{
			return ecs.AddComponent<Component>(args...);
		}

		template<typename Component>
		void RemoveComponent()
		{
			ecs.RemoveComponent<Component>();
		}

		ECS<IEntityComponent, Entity*>& GetEcs();

		void LoadEcs(ECS<IEntityComponent, Entity*>& newEcs);

		::std::vector<IEntityComponent*>& GetComponentList()
		{
			return ecs.GetComponentList();
		}

		Entity& operator=(const Entity& other);
	
	public:
		ResourceManager* rm;
		TransformComponent transform;
	private:
		ECS<IEntityComponent, Entity*> ecs;
		Engine* mEngine;
		Vec2 mPosition;
		Vec2 mSize;
		float mRotation;
		UUID mUUID;
	};
}
#endif // !ENTITY_H
