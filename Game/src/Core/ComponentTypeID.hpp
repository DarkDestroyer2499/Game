#ifndef COMPONENT_TYPE_ID_HPP
#define COMPONENT_TYPE_ID_HPP

namespace Oblivion
{
	using ComponentTypeID = unsigned int;

#define COMPONENT_TYPE_IMPL(ComponentClass) \
	virtual ComponentTypeID GetTypeID() const override \
	{ \
		return Oblivion::GetComponentTypeID<ComponentClass>(); \
	}

	namespace details
	{
		inline ComponentTypeID GetUniqueComponentTypeID()
		{
			static ComponentTypeID lastID = 0;
			return lastID++;
		}
	}
	
	template <typename T>
	inline ComponentTypeID GetComponentTypeID() noexcept
	{
		static const ComponentTypeID typeID = details::GetUniqueComponentTypeID();
		return typeID;
	}
}


#endif // !COMPONENT_TYPE_ID_HPP
