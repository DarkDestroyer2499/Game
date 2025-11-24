#ifndef ECS_HPP
#define ECS_HPP

#include <vector>
#include <unordered_map>
#include "ComponentTypeID.hpp"

namespace Oblivion
{
	template<typename T, typename OwnerType>
	class ECS
	{
	public:
		ECS();
		ECS(OwnerType owner);
		ECS(ECS&& other) noexcept;
		ECS(const ECS& other);
		~ECS();

		template<typename Component>
		bool HasComponent()
		{
			ComponentTypeID typeID = GetComponentTypeID<Component>();
			return mComponentMap.find(typeID) != mComponentMap.end();
		}

		template<typename Component>
		Component* GetComponent()
		{
			ComponentTypeID typeID = GetComponentTypeID<Component>();
			auto it = mComponentMap.find(typeID);
			if (it != mComponentMap.end())
				return static_cast<Component*>(it->second);

			return nullptr;
		}

		template<typename Component, typename... Args>
		Component* AddComponent(Args&&... args)
		{
			Component* newComponent = new Component(args...);
			newComponent->SetOwner(mOwner);
			mComponentList.push_back(newComponent);

			ComponentTypeID typeID = newComponent->GetTypeID();
			mComponentMap[typeID] = newComponent;

			newComponent->OnComponentAdded();

			return newComponent;
		}

		template<typename Component>
		void RemoveComponent()
		{
			ComponentTypeID typeID = GetComponentTypeID<Component>();

			auto it = mComponentMap.find(typeID);
			if (it != mComponentMap.end())
			{
				T* component = it->second;
				component->OnComponentRemoved();
				mComponentList.erase(::std::remove(mComponentList.begin(), mComponentList.end(), component), mComponentList.end());
				mComponentMap.erase(it);

				delete component;
			}

		}

		ECS& operator=(const ECS& other)
		{
			if (this == &other)
				return *this;

			for (auto* component : mComponentList)
				delete component;

			mComponentList.clear();
			mComponentMap.clear();

			for (auto& component : other.mComponentList)
			{
				auto newComponent = component->Clone();
				newComponent->SetOwner(mOwner);

				T* tmp = newComponent.release();
				mComponentList.push_back(tmp);

				ComponentTypeID typeID = tmp->GetTypeID();
				mComponentMap[typeID] = tmp;
			}
			return *this;
		}

		::std::vector<T*>& GetComponentList();

	private:
		OwnerType mOwner;
		::std::vector<T*> mComponentList;
		::std::unordered_map<ComponentTypeID, T*> mComponentMap;
	};

	template<typename T, typename OwnerType>
	inline ECS<T, OwnerType>::ECS()
		: mOwner{ nullptr }
	{
	}

	template<typename T, typename OwnerType>
	inline ECS<T, OwnerType>::ECS(OwnerType owner)
		: mOwner{ owner }
	{
	}

	template<typename T, typename OwnerType>
	inline ECS<T, OwnerType>::ECS(ECS&& other) noexcept
		: mOwner{ other.mOwner }, mComponentList{ std::move(other.mComponentList) },
		mComponentMap{ std::move(other.mComponentMap) }
	{
		other.mOwner = nullptr;
	}

	template<typename T, typename OwnerType>
	inline ECS<T, OwnerType>::ECS(const ECS& other)
		: mOwner{ other.mOwner }
	{
		for (auto& component : other.mComponentList)
		{
			auto newComponent = component->Clone();
			newComponent->SetOwner(other.mOwner);

			T* tmp = newComponent.release();

			mComponentList.push_back(tmp);

			ComponentTypeID typeID = tmp->GetTypeID();
			mComponentMap[typeID] = tmp;
		}
	}

	template<typename T, typename OwnerType>
	inline ECS<typename T, typename OwnerType>::~ECS()
	{
		for (auto& component : mComponentList)
		{
			delete component;
		}
	}

	template<typename T, typename OwnerType>
	inline ::std::vector<T*>& ECS<typename T, typename OwnerType>::GetComponentList()
	{
		return mComponentList;
	}
}

#endif // !ECS_HPP
