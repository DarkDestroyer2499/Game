#ifndef I_COMPONENT_H
#define I_COMPONENT_H

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../ComponentTypeID.hpp"

namespace Oblivion
{
#define COMPONENT_NAME (::std::string(__FILE__).substr(::std::string(__FILE__).find_last_of("/\\") + 1)).substr(0, (::std::string(__FILE__).substr(::std::string(__FILE__).find_last_of("/\\") + 1)).find_first_of('.'))

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
		virtual const char* GetName() { return mName.c_str(); };
	protected:
		Entity* mOwner;
		::std::string mName;
	};
}
#endif // !I_COMPONENT_H
