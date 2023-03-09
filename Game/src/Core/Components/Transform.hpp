#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "IEntityComponent.hpp"
#include "Util/Util.hpp"

namespace Oblivion
{
	class TransformComponent : public IEntityComponent
	{
	public:
		TransformComponent();
		~TransformComponent();

		void Update(const float&) override;
		void SetPosition(Vec2 newPosition);
		Vec2 GetPosition();
		void SetRotation(float newRotation);
		float GetRotation();
	};
}
#endif // !TRANSFORM_H
