#include "SFMLEventTranslator.hpp"

#include <unordered_set>

#include "EventBus.hpp"
#include "Events.hpp"
#include "Util/Log.hpp"

namespace Oblivion
{
	void SFMLEventTranslator::TranslateEvent(const sf::Event& event, EventBus& eventBus)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			eventBus.Publish(WindowClosedEvent{});
			break;

		case sf::Event::Resized:
			eventBus.Publish(WindowResizedEvent{ event.size });
			break;


		case sf::Event::MouseButtonPressed:
			eventBus.Publish(MouseButtonPressedEvent{ event.mouseButton });
			break;

		case sf::Event::MouseButtonReleased:
			eventBus.Publish(MouseButtonReleasedEvent{ event.mouseButton });
			break;

		case sf::Event::MouseMoved:
			eventBus.Publish(MouseMovedEvent{ event.mouseMove });
			break;

		case sf::Event::MouseWheelScrolled:
			eventBus.Publish(MouseWheelScrolledEvent{ event.mouseWheelScroll });
			break;

		case sf::Event::KeyPressed:
			eventBus.Publish(KeyPressedEvent{ event.key });
			break;

		case sf::Event::KeyReleased:
			eventBus.Publish(KeyReleasedEvent{ event.key });
			break;

		default: {
			static std::unordered_set<int> warnedTypes;
			if (warnedTypes.insert(event.type).second)
				Log(WARNING, "No channel for SFML event type: " << event.type);
			break;
		}
		}
	}
}
