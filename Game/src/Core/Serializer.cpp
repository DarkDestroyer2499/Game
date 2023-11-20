#include "Serializer.hpp"
#include <filesystem>

namespace YAML
{
	template<>
	struct convert<sf::IntRect>
	{
		static Node encode(const sf::IntRect& rect)
		{
			Node node;
			node.push_back(rect.left);
			node.push_back(rect.top);
			node.push_back(rect.width);
			node.push_back(rect.height);
			return node;
		}

		static bool decode(const Node& node, sf::IntRect& rect)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rect = sf::IntRect(node[0].as<int>(), node[1].as<int>(), node[2].as<int>(), node[3].as<int>());
			return true;
		}
	};

	template<>
	struct convert<b2BodyType>
	{
		static Node encode(const b2BodyType& type)
		{
			Node node;
			node.push_back(static_cast<int>(type));
			return node;
		}

		static bool decode(const Node& node, b2BodyType& rect)
		{
			if (!node.IsSequence() || node.size() != 1)
				return false;

			rect = static_cast<b2BodyType>(node.as<int>());
			return true;
		}
	};

	template<>
	struct convert<b2Vec2>
	{
		static Node encode(const b2Vec2& vec)
		{
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			return node;
		}

		static bool decode(const Node& node, struct b2Vec2& vec)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			vec = struct b2Vec2(node[0].as<float>(), node[1].as<float>());
			return true;
		}
	};

	template<>
	struct convert<Oblivion::Vec2>
	{
		static Node encode(const Oblivion::Vec2& vec)
		{
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			return node;
		}

		static bool decode(const Node& node, Oblivion::Vec2& vec)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			vec = { node[0].as<float>(), node[1].as<float>() };
			return true;
		}
	};

	Emitter& operator<<(Emitter& out, const sf::IntRect& rect)
	{
		out << Flow << BeginSeq << rect.left << rect.top << rect.width << rect.height << EndSeq;
		return out;
	}

	Emitter& operator<<(Emitter& out, const b2Vec2& rect)
	{
		out << Flow << BeginSeq << rect.x << rect.y << EndSeq;
		return out;
	}

	Emitter& operator<<(Emitter& out, const b2BodyType& type)
	{
		out << static_cast<int>(type);
		return out;
	}

	Emitter& operator<<(Emitter& out, const Oblivion::Vec2& rect)
	{
		out << Flow << BeginSeq << rect.x << rect.y << EndSeq;
		return out;
	}
}

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

			entity->GetComponent<TagComponent>()->SetTag(ent["Tag"]["Tag"].as<std::string>());

			if (ent["AnimatedGraphics"])
			{
				auto* animatedGraphics = entity->AddComponent<AnimatedGraphicsComponent>();

				for (auto& node : ent["AnimatedGraphics"]["AnimationList"])
				{	
					animatedGraphics->AddAnimation(node.first.as<std::string>(),
						*entity->rm->resources.GetComponent<TextureComponent>()->GetTexture("../resources/fang.png"),
						node.second["StartPos"].as<Vec2>(),
						node.second["Size"].as<Vec2>(),
						node.second["FramesCount"].as<int>(),
						node.second["mSpeed"].as<float>(),
						node.second["mStep"].as<float>()
					);
					animatedGraphics->mAnimList[animatedGraphics->mCurrentAnimation].mCurrentFrame = node.second["mCurrentFrame"].as<float>();
				}
				animatedGraphics->mAnimList[animatedGraphics->mCurrentAnimation].isFlipped = ent["AnimatedGraphics"]["isFlipped"].as<bool>();
				animatedGraphics->mAnimList[animatedGraphics->mCurrentAnimation].isPlaying = ent["AnimatedGraphics"]["isPlaying"].as<bool>();
				animatedGraphics->mCurrentAnimation = ent["AnimatedGraphics"]["CurrentAnimation"].as<std::string>();
			}

			if (ent["Graphics"])
			{
				entity->AddComponent<GraphicsComponent>(*entity->rm->resources.GetComponent<TextureComponent>()->GetTexture(ent["Graphics"]["TexturePath"].as<std::string>()),
					ent["Graphics"]["SpriteRect"].as<sf::IntRect>());
			}

			if (ent["Physics"])
			{
				auto node = ent["Physics"];

				auto objectType = static_cast<PhysicsObjectType>(node["PhysicsObjectType"].as<int>());

				b2BodyDef bdef;
				bdef.type = static_cast<b2BodyType>(node["bdef"]["bdef.type"].as<int>());
				bdef.position = node["bdef"]["bdef.position"].as<b2Vec2>();
				bdef.allowSleep = node["bdef"]["bdef.allowSleep"].as<bool>();
				bdef.angle = node["bdef"]["bdef.angle"].as<float>();
				bdef.angularDamping = node["bdef"]["bdef.angularDamping"].as<float>();
				bdef.angularVelocity = node["bdef"]["bdef.angularVelocity"].as<float>();
				bdef.awake = node["bdef"]["bdef.awake"].as<bool>();
				bdef.bullet = node["bdef"]["bdef.bullet"].as<bool>();
				bdef.enabled = node["bdef"]["bdef.enabled"].as<bool>();
				bdef.fixedRotation = node["bdef"]["bdef.fixedRotation"].as<bool>();
				bdef.gravityScale = node["bdef"]["bdef.gravityScale"].as<float>();
				bdef.linearDamping = node["bdef"]["bdef.linearDamping"].as<float>();
				bdef.linearVelocity = node["bdef"]["bdef.linearVelocity"].as<b2Vec2>();

				b2FixtureDef fdef;
				fdef.density = node["b2FixtureDef"]["fdef.density"].as<float>();
				fdef.filter.categoryBits = node["b2FixtureDef"]["fdef.filter"]["fdef.filter.categoryBits"].as<uint16>();
				fdef.filter.groupIndex = node["b2FixtureDef"]["fdef.filter"]["fdef.filter.groupIndex"].as<uint16>();
				fdef.filter.maskBits = node["b2FixtureDef"]["fdef.filter"]["fdef.filter.maskBits"].as<uint16>();
				fdef.friction = node["b2FixtureDef"]["fdef.friction"].as<float>();
				fdef.isSensor = node["b2FixtureDef"]["fdef.isSensor"].as<bool>();
				fdef.restitution = node["b2FixtureDef"]["fdef.restitution"].as<float>();
				fdef.restitutionThreshold = node["b2FixtureDef"]["fdef.restitutionThreshold"].as<float>();
				fdef.shape = nullptr;

				Vec2 size = node["Size"].as<Vec2>();
				Vec2 position = node["Position"].as<Vec2>();
				float density = node["Density"].as<float>();

				entity->AddComponent<PhysicsComponent>(mEngine->GetMainWorld(), objectType, bdef, size, position, density);

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

		for (auto& component : entity.GetComponentList())
		{
			if (dynamic_cast<TagComponent*>(component) != nullptr)
			{
				auto* comp = dynamic_cast<TagComponent*>(component);
				mEmitter << Key << comp->GetName();
				mEmitter << BeginMap;
				mEmitter << Key << "Tag" << Value << comp->GetTag();
				mEmitter << EndMap;
			}
			else if (dynamic_cast<AnimatedGraphicsComponent*>(component) != nullptr)
			{
				auto* comp = dynamic_cast<AnimatedGraphicsComponent*>(component);
				mEmitter << Key << comp->GetName();
				mEmitter << BeginMap;
				mEmitter << Key << "CurrentAnimation" << Value << comp->mCurrentAnimation;
				mEmitter << Key << "TexturePath" << Value << entity.rm->resources.GetComponent<TextureComponent>()->GetTexturePath(comp->mAnimList[comp->mCurrentAnimation].GetTexture());
				mEmitter << Key << "isFlipped" << Value << comp->mAnimList[comp->mCurrentAnimation].isFlipped;
				mEmitter << Key << "isPlaying" << Value << comp->mAnimList[comp->mCurrentAnimation].isPlaying;
				mEmitter << Key << "AnimationList";
				mEmitter << BeginMap;
	
				for (auto& [name, animation] : comp->mAnimList)
				{
					mEmitter << Key << name;
					mEmitter << BeginMap;

					mEmitter << Key << "mCurrentFrame" << Value << animation.mCurrentFrame;
					mEmitter << Key << "mSpeed" << Value << animation.mSpeed;
					mEmitter << Key << "mStep" << Value << animation.mStep;
					mEmitter << Key << "FramesCount" << Value << animation.mFrames.size();
					mEmitter << Key << "StartPos" << Value << animation.mStartPos;
					mEmitter << Key << "Size" << Value << animation.mSize;

					mEmitter << EndMap;
				}
				mEmitter << EndMap;

				mEmitter << EndMap;
			}
			else if (dynamic_cast<PhysicsComponent*>(component) != nullptr)
			{
				auto* comp = dynamic_cast<PhysicsComponent*>(component);
				mEmitter << Key << comp->GetName();
				mEmitter << BeginMap;

				mEmitter << Key << "PhysicsObjectType" << Value << static_cast<int>(comp->GetPhysicsType());
				Serialize(comp->GetBodyDef());

				mEmitter << Key << "Size" << Value << Flow << BeginSeq << comp->GetSize().x << comp->GetSize().y << EndSeq;

				mEmitter << Key << "Position" << Value << Flow << BeginSeq << comp->GetPosition().x << comp->GetPosition().y << EndSeq;

				mEmitter << Key << "Density" << Value << comp->GetDensity();

				Serialize(comp->GetFixtureDef());

				mEmitter << EndMap;
			}
			else if (dynamic_cast<GraphicsComponent*>(component) != nullptr)
			{
				auto* comp = dynamic_cast<GraphicsComponent*>(component);
				mEmitter << Key << comp->GetName();
				mEmitter << BeginMap;
				mEmitter << Key << "TexturePath" << Value << entity.rm->resources.GetComponent<TextureComponent>()->GetTexturePath(comp->GetSprite().getTexture());
				auto spriteRect = comp->GetSprite().getTextureRect();
				mEmitter << Key << "SpriteRect" << Value << spriteRect;
				mEmitter << EndMap;
			}
		}
		mEmitter << EndMap;
	}

	void Serializer::Serialize(b2FixtureDef fdef)
	{
		using namespace YAML;

		mEmitter << Key << "b2FixtureDef";
		mEmitter << BeginMap;

		mEmitter << Key << "fdef.density" << Value << fdef.density;

		mEmitter << Key << "fdef.filter";
		mEmitter << BeginMap;
		mEmitter << Key << "fdef.filter.categoryBits" << Value << fdef.filter.categoryBits;
		mEmitter << Key << "fdef.filter.groupIndex" << Value << fdef.filter.groupIndex;
		mEmitter << Key << "fdef.filter.maskBits" << Value << fdef.filter.maskBits;
		mEmitter << EndMap;

		mEmitter << Key << "fdef.friction" << Value << fdef.friction;
		mEmitter << Key << "fdef.isSensor" << Value << fdef.isSensor;
		mEmitter << Key << "fdef.restitution" << Value << fdef.restitution;
		mEmitter << Key << "fdef.restitutionThreshold" << Value << fdef.restitutionThreshold;
		mEmitter << Key << "fdef.shape" << Value << fdef.shape;

		mEmitter << EndMap;
	}

	b2BodyDef Serializer::DeserializeBodyDef(YAML::Node& data)
	{
		using namespace YAML;

		b2BodyDef bdef;

		if (!data["bdef"])
		{
			Log(ERROR, "Tried to deserialize with no data!");
			return bdef;
		}

		bdef.type = static_cast<b2BodyType>(data["bdef"]["bdef.type"].as<int>());

		bdef.position = data["bdef"]["bdef.position"].as<b2Vec2>();

		bdef.allowSleep = data["bdef"]["bdef.allowSleep"].as<bool>();

		bdef.angle = data["bdef"]["bdef.angle"].as<float>();

		bdef.angularDamping = data["bdef"]["bdef.angularDamping"].as<float>();

		bdef.angularVelocity = data["bdef"]["bdef.angularVelocity"].as<float>();

		bdef.awake = data["bdef"]["bdef.awake"].as<bool>();

		bdef.bullet = data["bdef"]["bdef.bullet"].as<bool>();

		bdef.enabled = data["bdef"]["bdef.enabled"].as<bool>();

		bdef.fixedRotation = data["bdef"]["bdef.fixedRotation"].as<bool>();

		bdef.gravityScale = data["bdef"]["bdef.gravityScale"].as<float>();

		bdef.linearDamping = data["bdef"]["bdef.linearDamping"].as<float>();

		bdef.linearVelocity = data["bdef"]["bdef.linearVelocity"].as<b2Vec2>();

		return bdef;
	}

	b2FixtureDef Serializer::DeserializeFixtureDef(YAML::Node& data)
	{
		using namespace YAML;

		b2FixtureDef fdef;

		if (!data["b2FixtureDef"])
		{
			Log(ERROR, "Tried to deserialize with no data!");
			return fdef;
		}

		fdef.density = data["b2FixtureDef"]["fdef.density"].as<float>();

		fdef.density = data["b2FixtureDef"]["fdef.density"].as<float>();

		fdef.filter.categoryBits = data["b2FixtureDef"]["fdef.filter"]["fdef.filter.categoryBits"].as<uint16>();
		fdef.filter.groupIndex = data["b2FixtureDef"]["fdef.filter"]["fdef.filter.groupIndex"].as<uint16>();
		fdef.filter.maskBits = data["b2FixtureDef"]["fdef.filter"]["fdef.filter.maskBits"].as<uint16>();

		fdef.friction = data["b2FixtureDef"]["fdef.friction"].as<float>();
		fdef.isSensor = data["b2FixtureDef"]["fdef.isSensor"].as<bool>();

		fdef.restitution = data["b2FixtureDef"]["fdef.restitution"].as<float>();

		fdef.restitutionThreshold = data["b2FixtureDef"]["fdef.restitutionThreshold"].as<float>();

		return fdef;
	}

	void Serializer::Serialize(b2BodyDef bdef)
	{
		using namespace YAML;
		mEmitter << Key << "bdef";
		mEmitter << BeginMap;
		mEmitter << Key << "bdef.type" << Value << static_cast<int>(bdef.type);
		mEmitter << Key << "bdef.position" << Value << Flow << BeginSeq << bdef.position.x << bdef.position.y << EndSeq;
		mEmitter << Key << "bdef.allowSleep" << Value << bdef.allowSleep;
		mEmitter << Key << "bdef.angle" << Value << bdef.angle;
		mEmitter << Key << "bdef.angularDamping" << Value << bdef.angularDamping;
		mEmitter << Key << "bdef.angularVelocity" << Value << bdef.angularVelocity;
		mEmitter << Key << "bdef.awake" << Value << bdef.awake;
		mEmitter << Key << "bdef.bullet" << Value << bdef.bullet;
		mEmitter << Key << "bdef.enabled" << Value << bdef.enabled;
		mEmitter << Key << "bdef.fixedRotation" << Value << bdef.fixedRotation;
		mEmitter << Key << "bdef.gravityScale" << Value << bdef.gravityScale;
		mEmitter << Key << "bdef.linearDamping" << Value << bdef.linearDamping;
		mEmitter << Key << "bdef.linearVelocity" << Value << Flow << BeginSeq << bdef.linearVelocity.x << bdef.linearVelocity.y << EndSeq;
		mEmitter << EndMap;
	}
}
