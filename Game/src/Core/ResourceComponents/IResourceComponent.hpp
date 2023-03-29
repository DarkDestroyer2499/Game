#ifndef I_RESOURCE_COMPONENT_HPP
#define I_RESOURCE_COMPONENT_HPP

#include <string>

namespace Oblivion
{
#define COMPONENT_NAME (::std::string(__FILE__).substr(::std::string(__FILE__).find_last_of("/\\") + 1)).substr(0, (::std::string(__FILE__).substr(::std::string(__FILE__).find_last_of("/\\") + 1)).find_first_of('.'))

	class ResourceManager;

	class IResourceComponent
	{
	public:
		virtual ~IResourceComponent() = default;

		virtual void SetOwner(ResourceManager* newOwner) { mOwner = newOwner; }
		virtual const char* GetName() { return mName.c_str(); };
	protected:
		ResourceManager* mOwner;
		::std::string mName;
	};
}
#endif // !I_RESOURCE_COMPONENT_HPP
