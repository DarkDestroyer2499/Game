#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"
#include "../../Core/EventSystem/Events.hpp"

namespace Oblivion
{
	class CameraComponent : public IEditorComponent
	{
	public:
		COMPONENT_TYPE_IMPL(CameraComponent)
		CameraComponent(Editor*);
		~CameraComponent() = default;

		void Update() override;

		Vec2 GetCameraPos() const;

	private:
		void OnMouseWheelScrolled(const MouseWheelScrolledEvent&);
		void OnMouseButtonPressed(const MouseButtonPressedEvent&);
		void OnMouseButtonReleased(const MouseButtonReleasedEvent&);

	private:
		bool mIsPrimary, mMiddleButtonHold;
		float mCurrentZoom, mZoomDefault = 1;
		Editor* mEditor;
		sf::View mView;
		sf::RenderTexture* mTexture;
		Vec2 mPosition, mLastClickedPos;

	private:
		Subscription mMouseWheelScrolledEvent;
		Subscription mMouseButtonPressedEvent;
		Subscription mMouseButtonReleasedEvent;
	};
}
#endif // !CAMERA_HPP
