#ifndef EVENT_BROADCASTER_HPP
#define EVENT_BROADCASTER_HPP

#include <map>
#include "SFML/Graphics.hpp"
#include <list>

namespace Oblivion
{
	enum EventType
	{
		//SFML
		Closed,                 ///< The window requested to be closed (no data)
		Resized,                ///< The window was resized (data in event.size)
		LostFocus,              ///< The window lost the focus (no data)
		GainedFocus,            ///< The window gained the focus (no data)
		TextEntered,            ///< A character was entered (data in event.text)
		KeyPressed,             ///< A key was pressed (data in event.key)
		KeyReleased,            ///< A key was released (data in event.key)
		MouseWheelMoved,        ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
		MouseWheelScrolled,     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
		MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
		MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
		MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
		MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
		MouseLeft,              ///< The mouse cursor left the area of the window (no data)
		JoystickButtonPressed,  ///< A joystick button was pressed (data in event.joystickButton)
		JoystickButtonReleased, ///< A joystick button was released (data in event.joystickButton)
		JoystickMoved,          ///< The joystick moved along an axis (data in event.joystickMove)
		JoystickConnected,      ///< A joystick was connected (data in event.joystickConnect)
		JoystickDisconnected,   ///< A joystick was disconnected (data in event.joystickConnect)
		TouchBegan,             ///< A touch event began (data in event.touch)
		TouchMoved,             ///< A touch moved (data in event.touch)
		TouchEnded,             ///< A touch event ended (data in event.touch)
		SensorChanged,          ///< A sensor value changed (data in event.sensor)

		Count                   ///< Keep last -- the total number of event types
		//!SFML
		//OBLIVION

		//!OBLIVION
	};

	class Event
	{
	public:
		~Event() = default;

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

	class EventSubscriber : public Event {
	public:
		virtual ~EventSubscriber() = default;
	};

	class ISubject {
	public:
		virtual ~ISubject() = default;
		virtual void Attach(EventType, EventSubscriber* observer) = 0;
		virtual void Detach(EventType, EventSubscriber* observer) = 0;
		virtual void Notify(const sf::Event& event) = 0;
	};

	class EventBroadcaster : public ISubject
	{
	public:
		void Attach(EventType eventType, EventSubscriber* observer) override;
		void Detach(EventType, EventSubscriber* observer) override;
		void Notify(const sf::Event& event) override;
		void Notify(EventType event);

	private:
		std::map<EventType, std::list<EventSubscriber*>> mObserverList;
	};
}
#endif // !EVENT_BROADCASTER_HPP
