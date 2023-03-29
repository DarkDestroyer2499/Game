#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "Core/ECS.hpp"
#include "Core/ResourceComponents/IResourceComponent.hpp"

namespace Oblivion
{
	class ResourceManager
	{
	public:
		ResourceManager();

	public:
		ECS<IResourceComponent, ResourceManager*> resources;
	};
}
#endif // !RESOURCE_MANAGER_HPP
