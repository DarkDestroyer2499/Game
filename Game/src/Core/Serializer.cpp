#include "Serializer.hpp"
#include <filesystem>
#include "YamlConverters.hpp"
#include "Core/ComponentRegistry.hpp"

namespace Oblivion
{
	Serializer::Serializer(Engine* engine, Scene& scene)
		: mEngine{ engine }
	{
		Serialize(scene, "");
	}

	Serializer::Serializer(Engine* engine) :
		mEngine{ engine }
	{
	}

	void Serializer::Serialize(Scene& scene, ::std::filesystem::path filePath)
	{
		mStream.open(filePath.string() + ".yaml", std::fstream::trunc);

		if (mStream.is_open())
		{
			Log(SUCCESS, "Opened! " << filePath);
		}
		else
			Log(ERROR, "Not Opened! " << filePath);

		mEmitter << YAML::BeginMap;
		mEmitter << YAML::Key << "Scene" << YAML::Value << scene.GetName();
		mEmitter << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		for (auto& entity : scene.GetEntityList())
		{
			Serialize(entity);
		}

		mEmitter << YAML::EndSeq;
		mEmitter << YAML::EndMap;

		mStream << mEmitter.c_str();
		mStream.close();
	}

	bool Serializer::Deserialize(Scene& scene, ::std::filesystem::path filePath)
	{
		using namespace YAML;

		::std::ifstream file(filePath);
		::std::stringstream strStream;

		if (!file.is_open())
		{
			Log(ERROR, "File does not exist: " << filePath);
			return false;
		}

		strStream << file.rdbuf();

		Node data = Load(strStream.str());

		if (!data["Scene"])
		{
			file.close();
			Log(ERROR, "Scene was not found: " << filePath);
			return false;
		}

		std::string sceneName = data["Scene"].as<std::string>();

		scene.SetName(sceneName);

		Node entitiesNode = data["Entities"];

		if (!entitiesNode)
		{
			file.close();
			return false;
		}

		for (const auto& ent : entitiesNode)
		{
			Entity* entity = mEngine->CreateObject(scene);

			uintmax_t uuid = ent["Entity"].as<uintmax_t>();

			entity->SetUUID(uuid);

			if (ent["Name"])
				entity->SetName(ent["Name"].as<std::string>());
			else if (ent["Tag"])
				entity->SetName(ent["Tag"]["Tag"].as<std::string>());

			for (const ComponentDescriptor& desc : GetComponentRegistry().All())
			{
				if (desc.deserialize && ent[desc.name])
					desc.deserialize(ent[desc.name], *entity);
			}
		}

		file.close();
		return true;
	}

	void Serializer::Serialize(Entity& entity)
	{
		using namespace YAML;

		mEmitter << BeginMap;
		mEmitter << Key << "Entity" << Value << (uintmax_t)entity.GetUUID();
		mEmitter << Key << "Name" << Value << entity.GetName();

		for (auto& component : entity.GetComponentList())
		{
			const ComponentDescriptor* desc = GetComponentRegistry().FindByType(component->GetTypeID());
			if (desc && desc->serialize)
			{
				mEmitter << Key << desc->name;
				desc->serialize(mEmitter, component, entity);
			}
		}
		mEmitter << EndMap;
	}




}
