#ifndef SYSTEM_EVENT_HPP
#define SYSTEM_EVENT_HPP

#include "IEvent.hpp"
#include <SFML/Graphics.hpp>

namespace Oblivion
{
	class SystemEvent : public IEvent
	{
	public:
		virtual ~SystemEvent() = default;

		virtual void OnWindowClosed() {};
		virtual void OnResized(const sf::Event&) {};
		virtual void OnLostFocus() {};
		virtual void OnGainedFocus() {};
		virtual void OnTextEntered(const sf::Event&) {};
		virtual void OnKeyPressed(const sf::Event&) {};
		virtual void OnKeyReleased(const sf::Event&) {};
		virtual void OnMouseWheelMoved(const sf::Event&) {};
		virtual void OnMouseWheelScrolled(const sf::Event&) {};
		virtual void OnMouseButtonPressed(const sf::Event&) {};
		virtual void OnMouseButtonReleased(const sf::Event&) {};
		virtual void OnMouseMoved(const sf::Event&) {};
		virtual void OnMouseEntered() {};
		virtual void OnMouseLeft() {};
		virtual void OnJoystickButtonPressed(const sf::Event&) {};
		virtual void OnJoystickButtonReleased(const sf::Event&) {};
		virtual void OnJoystickMoved(const sf::Event&) {};
		virtual void OnJoystickConnected(const sf::Event&) {};
		virtual void OnJoystickDisconnected(const sf::Event&) {};
		virtual void OnTouchBegan(const sf::Event&) {};
		virtual void OnTouchMoved(const sf::Event&) {};
		virtual void OnTouchEnded(const sf::Event&) {};
		virtual void OnSensorChanged(const sf::Event&) {};
	};
}
#endif // !SYSTEM_EVENT_HPP
