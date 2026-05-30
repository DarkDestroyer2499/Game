#ifndef I_COMPONENT_H
#define I_COMPONENT_H

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../ComponentTypeID.hpp"

namespace Oblivion
{
	class Entity;

	class IEntityComponent
	{
	public:
		virtual ~IEntityComponent() = default;

		virtual ::std::unique_ptr<IEntityComponent> Clone() const = 0;
		virtual void Update(float) = 0;
		virtual void Render(sf::RenderTarget*) = 0;

		virtual ComponentTypeID GetTypeID() const = 0;

		virtual void SetOwner(Entity* newOwner) { mOwner = newOwner; }
		virtual const char* GetName();

		virtual void OnComponentAdded() {}
		virtual void OnComponentRemoved() {}


	protected:
		Entity* mOwner = nullptr;
	};
}
#endif // !I_COMPONENT_H
