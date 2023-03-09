#include "ID.hpp"
#include "Util/Log.hpp"

namespace Oblivion
{

	IDComponent::IDComponent()
		: mUUID{ UUID() }
	{
		mName = COMPONENT_NAME;
	}

	void IDComponent::Update(const float& time)
	{
	}

	UUID IDComponent::GetUUID() const
	{
		return mUUID;
	}
}