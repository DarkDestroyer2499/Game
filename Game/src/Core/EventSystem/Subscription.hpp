#ifndef SUBSCRIPTION_HPP
#define SUBSCRIPTION_HPP

#include <functional>

namespace Oblivion
{
	struct Subscription
	{
		Subscription() = default;

		Subscription(std::function<void()> unsubscribeFunc)
			: mUnsubscribe(unsubscribeFunc)
		{}

		Subscription(const Subscription& other) = delete;

		Subscription& operator=(const Subscription& other) = delete;

		Subscription(Subscription&& other) noexcept
			: mUnsubscribe(std::move(other.mUnsubscribe))
		{
			other.mUnsubscribe = nullptr;
		}

		Subscription& operator=(Subscription&& other) noexcept
		{
			if (this != &other)
			{
				Reset();
				mUnsubscribe = std::move(other.mUnsubscribe);
				other.mUnsubscribe = nullptr;
			}
			return *this;
		}

		~Subscription()
		{
			if (mUnsubscribe)
				mUnsubscribe();
		}

		void Reset()
		{
			if (mUnsubscribe)
				mUnsubscribe();
			mUnsubscribe = nullptr;
		}

	private:
		std::function<void()> mUnsubscribe;
	};
}// namespace Oblivion
#endif // !SUBSCRIPTION_HPP
