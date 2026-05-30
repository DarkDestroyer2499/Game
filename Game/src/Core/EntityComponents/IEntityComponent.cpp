#include "IEntityComponent.hpp"
#include "Core/ComponentRegistry.hpp"

namespace Oblivion
{
	const char* IEntityComponent::GetName()
	{
		const ComponentDescriptor* desc = GetComponentRegistry().FindByType(GetTypeID());
		return desc ? desc->name.c_str() : "Unknown";
	}
}
