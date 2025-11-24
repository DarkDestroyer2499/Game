#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <functional>
#include <vector>


#include "IEntityComponent.hpp"
#include "Util/Util.hpp"



namespace Oblivion
{
	class TransformComponent : public IEntityComponent
	{
	public:

		COMPONENT_TYPE_IMPL(TransformComponent)

		TransformComponent();
		~TransformComponent();

		::std::unique_ptr<IEntityComponent> Clone() const override;
		void Update(float) override;
		void Render(sf::RenderTarget* target) override;

		using TransformChangedCallback = ::std::function<void(const Vec2&, float)>;

		void SubscribeToTransformChanged(const TransformChangedCallback& callback);

		void SetPosition(const Vec2& pos);
		void SetRotation(float rot);

		void SetPositionSilent(const Vec2& pos);
		void SetRotationSilent(float rot);

	private:
		void NotifyTransformChanged();

	public:
		Vec2 position;
		float rotation;

	private:
		std::vector<TransformChangedCallback> mTransformChangedCallbacks;
		Vec2 mLastPosition;
		float mLastRotation;
	};
}
#endif // !TRANSFORM_H
