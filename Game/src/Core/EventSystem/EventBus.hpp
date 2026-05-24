#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP

#include <unordered_map>
#include <typeindex>
#include <vector>
#include <functional>
#include <memory>

#include "Subscription.hpp"

namespace Oblivion
{
	class EventBus
	{
	private:
		struct ChannelBase {
			virtual ~ChannelBase() = default;
		};

		template <typename T>
		struct Channel : public ChannelBase {
			size_t nextId = 0;
			std::unordered_map<size_t, std::function<void(const T&)>> subscribers;
		};

		template <typename T>
		Channel<T>& GetChannel()
		{
			auto& slot = mChannels[typeid(T)];
			if (!slot)
				slot = std::make_unique<Channel<T>>();

			return *static_cast<Channel<T>*>(slot.get());
		}
	public:
		template <typename T>
		[[nodiscard]] Subscription Subscribe(std::function<void(const T&)> callback)
		{
			auto& ch = GetChannel<T>();
			size_t id = ch.nextId++;
			ch.subscribers.emplace(id, std::move(callback));
			return Subscription{
				[this, id]() {
					GetChannel<T>().subscribers.erase(id);
				}
			};
		}

		template <typename T>
		void Publish(const T& event)
		{
			auto it = mChannels.find(typeid(T));

			if (it == mChannels.end()) 
				return;

			auto& ch = static_cast<Channel<T>&>(*it->second);

			for (auto& [id, cb] : ch.subscribers)
				cb(event);
		}


	private:
		std::unordered_map<std::type_index, std::unique_ptr<ChannelBase>> mChannels;
	};

} // namespace Oblivion

#endif // !EVENT_BUS_HPP
