#ifndef ID_H
#define ID_H

#include "IEntityComponent.hpp"
#include "Core/UUID.hpp"

namespace Oblivion
{

	class IDComponent : public IEntityComponent
	{
	public:
		IDComponent();
		~IDComponent() = default;

		void Update(const float&) override;
		UUID GetUUID() const;
	private:
		UUID mUUID;
	};

}
#endif // !ID_H
