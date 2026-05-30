#ifndef SFML_EVENT_TRANSLATOR_HPP
#define SFML_EVENT_TRANSLATOR_HPP

#include <SFML/Window/Event.hpp>

namespace Oblivion
{
	class EventBus;
	class SFMLEventTranslator
	{
	public:
		static void TranslateEvent(const sf::Event& event, EventBus& eventBus);
	};
} // namespace Oblivion

#endif // !SFML_EVENT_TRANSLATOR_HPP
