#ifndef UUID_HPP
#define UUID_HPP

#include <xhash>

namespace Oblivion
{
	class UUID
	{
	public:
		UUID();
		UUID(uintmax_t uuid);

		operator uintmax_t() const { return mUUID; }

	private:
		uintmax_t mUUID;
	};
}
#endif // !UUID_HPP
