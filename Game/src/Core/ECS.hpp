#ifndef ECS_HPP
#define ECS_HPP

#include <vector>

namespace Oblivion
{
	template<typename T, typename OwnerType>
	class ECS
	{
	public:
		ECS();
		ECS(OwnerType owner);
		ECS(ECS&& other);
		ECS(const ECS& other);
		~ECS();

		template<typename Component>
		bool HasComponent()
		{
			for (auto& component : mComponentList)
			{
				if (dynamic_cast<Component*>(component))
					return true;
			}
			return false;
		}

		template<typename Component>
		Component* GetComponent()
		{
			for (auto& component : mComponentList)
			{
				Component* tmp = dynamic_cast<Component*>(component);
				if (tmp)
					return tmp;
			}
			return nullptr;
		}

		template<typename Component, typename... Args>
		Component* AddComponent(Args&&... args)
		{
			Component* tmpComponent = new Component(args...);
			tmpComponent->SetOwner(mOwner);
			mComponentList.push_back(tmpComponent);
			return tmpComponent;
		}

		template<typename Component>
		void RemoveComponent()
		{
			Component* tmpComponent = this->GetComponent<Component>();
			if (tmpComponent != nullptr)
			{
				this->mComponentList.erase(::std::remove(this->mComponentList.begin(), this->mComponentList.end(), tmpComponent), this->mComponentList.end());
				delete tmpComponent;
			}
		}

		ECS& operator=(const ECS& other)
		{
			if (this == &other)
				return *this;
			mOwner = other.mOwner;
			for (auto& component : other.mComponentList)
			{
				auto newComponent = component->Clone();
				newComponent->SetOwner(other.mOwner);
				mComponentList.push_back(newComponent.release());
			}
			return *this;
		}

		::std::vector<T*>& GetComponentList();

	private:
		::std::vector<T*> mComponentList;
		OwnerType mOwner;
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
	inline ECS<T, OwnerType>::ECS(ECS&& other)
		: mOwner{ other.mOwner }, mComponentList{ other.mComponentList }
	{
		other.mOwner = nullptr;
		for (auto& component : other.mComponentList)
		{
			component = nullptr;
		}
	}

	template<typename T, typename OwnerType>
	inline ECS<T, OwnerType>::ECS(const ECS& other)
		: mOwner{ other.mOwner }
	{
		for (auto& component : other.mComponentList)
		{
			auto newComponent = component->Clone();
			newComponent->SetOwner(other.mOwner);
			mComponentList.push_back(newComponent.release());
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
