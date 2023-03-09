#include <random>
#include "Core/UUID.hpp"

namespace Oblivion
{
	static ::std::random_device sRandomDevice;
	static ::std::mt19937_64 sEngine(sRandomDevice());
	static ::std::uniform_int_distribution<uintmax_t> sUniformDistribution;

	UUID::UUID()
		: mUUID{ sUniformDistribution(sEngine) }
	{
	}

	UUID::UUID(uintmax_t uuid)
		: mUUID{ uuid }
	{
	}
}

namespace std
{
	template<>
	struct hash<Oblivion::UUID>
	{
		uintmax_t operator()(const Oblivion::UUID& uuid)
		{
			return hash<uintmax_t>()((uintmax_t)uuid);
		}
	};
}
