#ifndef ID_HPP
#define ID_HPP

#include "IEntityComponent.hpp"
#include "Core/UUID.hpp"

namespace Oblivion
{
	class IDComponent : public IEntityComponent
	{
	public:
		IDComponent();
		IDComponent(UUID uuid);
		~IDComponent() = default;

		::std::unique_ptr<IEntityComponent> Clone() const override;
		void SetUUID(UUID uuid);
		void Update(const float&) override;
		UUID GetUUID() const;

	private:
		UUID mUUID;
	};

}
#endif // !ID_HPP
