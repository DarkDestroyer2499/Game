#ifndef COMPONENT_REGISTRY_HPP
#define COMPONENT_REGISTRY_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "yaml.h"
#include "ComponentTypeID.hpp"

namespace Oblivion
{
	class Entity;
	class Editor;
	class IEntityComponent;

	struct ComponentDescriptor
	{
		std::string name;
		std::function<void(YAML::Emitter&, IEntityComponent*, Entity&)> serialize;
		std::function<void(const YAML::Node&, Entity&)> deserialize;
		std::function<void(IEntityComponent*, Editor&)> drawInspector;
		std::function<void(Entity&)> create;
		ComponentTypeID typeID = 0;
	};

	class ComponentRegistry
	{
	public:
		template<typename T>
		void Register(ComponentDescriptor descriptor)
		{
			ComponentTypeID id = GetComponentTypeID<T>();
			descriptor.typeID = id;
			size_t index = mDescriptors.size();
			mByType[id] = index;
			mByName[descriptor.name] = index;
			mDescriptors.push_back(std::move(descriptor));
		}

		const ComponentDescriptor* FindByType(ComponentTypeID id) const
		{
			auto it = mByType.find(id);
			return it == mByType.end() ? nullptr : &mDescriptors[it->second];
		}

		const ComponentDescriptor* FindByName(const std::string& name) const
		{
			auto it = mByName.find(name);
			return it == mByName.end() ? nullptr : &mDescriptors[it->second];
		}

		const std::vector<ComponentDescriptor>& All() const { return mDescriptors; }

	private:
		std::vector<ComponentDescriptor> mDescriptors;
		std::unordered_map<ComponentTypeID, size_t> mByType;
		std::unordered_map<std::string, size_t> mByName;
	};

	ComponentRegistry& GetComponentRegistry();
	void RegisterComponents();
}
#endif // !COMPONENT_REGISTRY_HPP
