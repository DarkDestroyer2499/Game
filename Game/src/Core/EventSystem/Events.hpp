#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SFML/Window/Event.hpp>

namespace Oblivion
{
	class Entity;

	//Oblivion events

	struct EntityCreatedEvent
	{
		Entity* entity;
	};

	struct EntityRemovedEvent
	{
		Entity* entity;
	};

	//Editor events
	struct WindowClosedEvent {};
	struct WindowResizedEvent
	{
		unsigned int width;
		unsigned int height;

		WindowResizedEvent(const sf::Event::SizeEvent& event)
			: width{ event.width }, height{ event.height } {}
	};

	struct MouseButtonPressedEvent
	{
		sf::Mouse::Button button;
		int x, y;
		MouseButtonPressedEvent(const sf::Event::MouseButtonEvent& event)
			: button{ event.button }, x{ event.x }, y{ event.y } {}
	};

	struct MouseButtonReleasedEvent
	{
		sf::Mouse::Button button;
		int x, y;
		MouseButtonReleasedEvent(const sf::Event::MouseButtonEvent& event)
			: button{ event.button }, x{ event.x }, y{ event.y } {}
	};

	struct MouseMovedEvent
	{
		int x, y;
		MouseMovedEvent(const sf::Event::MouseMoveEvent& event)
			: x{ event.x }, y{ event.y } {}
	};

	struct MouseWheelScrolledEvent
	{
		MouseWheelScrolledEvent(const sf::Event::MouseWheelScrollEvent& event)
			: wheel{ event.wheel }, delta{ event.delta }, x{ event.x }, y{ event.y } {}


		sf::Mouse::Wheel wheel;
		float delta;
		int x, y;
	};

	struct KeyPressedEvent
	{
		sf::Keyboard::Key code;
		bool alt, control, shift, system;
		KeyPressedEvent(const sf::Event::KeyEvent& event)
			: code{ event.code }, alt{ event.alt }, control{ event.control }, shift{ event.shift }, system{ event.system } {}
	};

	struct KeyReleasedEvent
	{
		sf::Keyboard::Key code;
		bool alt, control, shift, system;
		KeyReleasedEvent(const sf::Event::KeyEvent& event)
			: code{ event.code }, alt{ event.alt }, control{ event.control }, shift{ event.shift }, system{ event.system } {}
	};

}



#endif // !EVENTS_HPP