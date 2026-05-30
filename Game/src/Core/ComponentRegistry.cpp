#include "ComponentRegistry.hpp"

namespace Oblivion
{
	ComponentRegistry& GetComponentRegistry()
	{
		static ComponentRegistry registry;
		return registry;
	}
}
