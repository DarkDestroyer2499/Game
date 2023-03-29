#include "ID.hpp"
#include "Util/Log.hpp"

namespace Oblivion
{

	IDComponent::IDComponent()
		: mUUID{ UUID() }
	{
		mName = COMPONENT_NAME;
	}

	IDComponent::IDComponent(UUID uuid)
		:mUUID{uuid}
	{
	}

	void IDComponent::SetUUID(UUID uuid)
	{
		mUUID = uuid;
	}

	::std::unique_ptr<IEntityComponent> IDComponent::Clone() const
	{
		return ::std::make_unique<IDComponent>(*this);
	}

	void IDComponent::Update(const float& time)
	{
	}

	UUID IDComponent::GetUUID() const
	{
		return mUUID;
	}
}