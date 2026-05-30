#include "ComponentRegistry.hpp"
#include "YamlConverters.hpp"
#include "InspectorWidgets.hpp"
#include "Entity.hpp"
#include "Engine.hpp"
#include "ResourceManager.hpp"
#include "EntityComponents/ComponentLinker.hpp"
#include "ResourceComponents/ResourceComponentLinker.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

namespace Oblivion
{
	static void WriteBodyDef(YAML::Emitter& emitter, const b2BodyDef& bdef)
	{
		using namespace YAML;
		emitter << Key << "bdef";
		emitter << BeginMap;
		emitter << Key << "bdef.type" << Value << static_cast<int>(bdef.type);
		emitter << Key << "bdef.position" << Value << Flow << BeginSeq << bdef.position.x << bdef.position.y << EndSeq;
		emitter << Key << "bdef.allowSleep" << Value << bdef.allowSleep;
		emitter << Key << "bdef.angle" << Value << bdef.angle;
		emitter << Key << "bdef.angularDamping" << Value << bdef.angularDamping;
		emitter << Key << "bdef.angularVelocity" << Value << bdef.angularVelocity;
		emitter << Key << "bdef.awake" << Value << bdef.awake;
		emitter << Key << "bdef.bullet" << Value << bdef.bullet;
		emitter << Key << "bdef.enabled" << Value << bdef.enabled;
		emitter << Key << "bdef.fixedRotation" << Value << bdef.fixedRotation;
		emitter << Key << "bdef.gravityScale" << Value << bdef.gravityScale;
		emitter << Key << "bdef.linearDamping" << Value << bdef.linearDamping;
		emitter << Key << "bdef.linearVelocity" << Value << Flow << BeginSeq << bdef.linearVelocity.x << bdef.linearVelocity.y << EndSeq;
		emitter << EndMap;
	}

	static void WriteFixtureDef(YAML::Emitter& emitter, const b2FixtureDef& fdef)
	{
		using namespace YAML;
		emitter << Key << "b2FixtureDef";
		emitter << BeginMap;
		emitter << Key << "fdef.density" << Value << fdef.density;
		emitter << Key << "fdef.filter";
		emitter << BeginMap;
		emitter << Key << "fdef.filter.categoryBits" << Value << fdef.filter.categoryBits;
		emitter << Key << "fdef.filter.groupIndex" << Value << fdef.filter.groupIndex;
		emitter << Key << "fdef.filter.maskBits" << Value << fdef.filter.maskBits;
		emitter << EndMap;
		emitter << Key << "fdef.friction" << Value << fdef.friction;
		emitter << Key << "fdef.isSensor" << Value << fdef.isSensor;
		emitter << Key << "fdef.restitution" << Value << fdef.restitution;
		emitter << Key << "fdef.restitutionThreshold" << Value << fdef.restitutionThreshold;
		emitter << EndMap;
	}

	void SerializeAnimatedGraphics(YAML::Emitter& emitter, AnimatedGraphicsComponent* comp, Entity& entity)
	{
		using namespace YAML;
		emitter << BeginMap;
		emitter << Key << "CurrentAnimation" << Value << comp->mCurrentAnimation;
		emitter << Key << "TexturePath" << Value << entity.rm->resources.GetComponent<TextureComponent>()->GetTexturePath(comp->mAnimList[comp->mCurrentAnimation].GetTexture());
		emitter << Key << "isFlipped" << Value << comp->mAnimList[comp->mCurrentAnimation].isFlipped;
		emitter << Key << "isPlaying" << Value << comp->mAnimList[comp->mCurrentAnimation].isPlaying;
		emitter << Key << "AnimationList";
		emitter << BeginMap;
		for (auto& [name, animation] : comp->mAnimList)
		{
			emitter << Key << name;
			emitter << BeginMap;
			emitter << Key << "mCurrentFrame" << Value << animation.mCurrentFrame;
			emitter << Key << "mSpeed" << Value << animation.mSpeed;
			emitter << Key << "mStep" << Value << animation.mStep;
			emitter << Key << "FramesCount" << Value << animation.mFrames.size();
			emitter << Key << "StartPos" << Value << animation.mStartPos;
			emitter << Key << "Size" << Value << animation.mSize;
			emitter << EndMap;
		}
		emitter << EndMap;
		emitter << EndMap;
	}

	void DeserializeAnimatedGraphics(const YAML::Node& node, Entity& entity)
	{
		auto* animatedGraphics = entity.AddComponent<AnimatedGraphicsComponent>();
		auto* texComp = entity.rm->resources.GetComponent<TextureComponent>();
		sf::Texture* tex = texComp->GetOrLoadTexture(node["TexturePath"].as<std::string>());

		for (auto& anim : node["AnimationList"])
		{
			animatedGraphics->AddAnimation(anim.first.as<std::string>(),
				*tex,
				anim.second["StartPos"].as<Vec2>(),
				anim.second["Size"].as<Vec2>(),
				anim.second["FramesCount"].as<int>(),
				anim.second["mSpeed"].as<float>(),
				anim.second["mStep"].as<float>()
			);
			animatedGraphics->mAnimList[animatedGraphics->mCurrentAnimation].mCurrentFrame = anim.second["mCurrentFrame"].as<float>();
		}
		animatedGraphics->mAnimList[animatedGraphics->mCurrentAnimation].isFlipped = node["isFlipped"].as<bool>();
		animatedGraphics->mAnimList[animatedGraphics->mCurrentAnimation].isPlaying = node["isPlaying"].as<bool>();
		animatedGraphics->mCurrentAnimation = node["CurrentAnimation"].as<std::string>();
	}

	void RegisterComponents()
	{
		static bool done = false;
		if (done)
			return;
		done = true;

		ComponentRegistry& registry = GetComponentRegistry();

		registry.Register<TransformComponent>({
			"Transform",
			nullptr,
			nullptr,
			[](IEntityComponent* component, Editor& editor)
			{
				auto* transform = static_cast<TransformComponent*>(component);
				if (!Inspector::BeginComponent(component))
					return;

				Vec2 position = transform->position;
				if (Inspector::DragVec2("Position", position, 0.f, 0.1f))
					transform->SetPosition(position);

				float rotation = transform->rotation * DEG_IN_RAD;
				if (Inspector::DragFloat("Rotation", rotation, 0.f, 0.5f, "%.1f"))
					transform->SetRotation(rotation / DEG_IN_RAD);

				Inspector::EndComponent();
			}
		});

		registry.Register<GraphicsComponent>({
			"Graphics",
			[](YAML::Emitter& emitter, IEntityComponent* component, Entity& entity)
			{
				auto* comp = static_cast<GraphicsComponent*>(component);
				emitter << YAML::BeginMap;
				emitter << YAML::Key << "TexturePath" << YAML::Value
					<< entity.rm->resources.GetComponent<TextureComponent>()->GetTexturePath(comp->GetSprite().getTexture());
				emitter << YAML::Key << "SpriteRect" << YAML::Value << comp->GetSprite().getTextureRect();
				emitter << YAML::EndMap;
			},
			[](const YAML::Node& node, Entity& entity)
			{
				entity.AddComponent<GraphicsComponent>(
					*entity.rm->resources.GetComponent<TextureComponent>()->GetTexture(node["TexturePath"].as<std::string>()),
					node["SpriteRect"].as<sf::IntRect>());
			},
			[](IEntityComponent* component, Editor& editor)
			{
				auto* comp = static_cast<GraphicsComponent*>(component);
				if (!Inspector::BeginComponent(component))
					return;

				static Vec2 SpriteIconSize{ 100.f, 100.f };
				sf::Sprite tmpSprite = comp->GetSprite();
				tmpSprite.setRotation(0);
				sf::IntRect rect = tmpSprite.getTextureRect();

				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.14f, 0.14f, 0.15f, 1.00f));
				ImGui::BeginChild("SpritePreview", ImVec2(0, 140), true);
				if (rect.width > 0 && rect.height > 0)
				{
					ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - SpriteIconSize.x) / 2.0f + 8.0f);
					ImGui::SetCursorPosY(8.0f);
					tmpSprite.setScale({ SpriteIconSize.x / rect.width, SpriteIconSize.y / rect.height });
					ImGui::Image(tmpSprite);
				}
				ImGui::EndChild();
				ImGui::PopStyleColor();
				ImGui::Spacing();

				std::string sizeText = std::to_string(rect.width) + " x " + std::to_string(rect.height);
				Inspector::LabeledText("Texture", sizeText.c_str());

				Inspector::EndComponent();
			},
			[](Entity& entity) { entity.AddComponent<GraphicsComponent>(); }
		});

		registry.Register<AnimatedGraphicsComponent>({
			"AnimatedGraphics",
			[](YAML::Emitter& emitter, IEntityComponent* component, Entity& entity)
			{
				SerializeAnimatedGraphics(emitter, static_cast<AnimatedGraphicsComponent*>(component), entity);
			},
			[](const YAML::Node& node, Entity& entity)
			{
				DeserializeAnimatedGraphics(node, entity);
			},
			[](IEntityComponent* component, Editor& editor)
			{
				auto* comp = static_cast<AnimatedGraphicsComponent*>(component);
				if (!Inspector::BeginComponent(component))
					return;

				Inspector::LabeledText("Current", comp->GetCurrentAnimation().c_str());
				Inspector::LabeledText("Clips", std::to_string(comp->GetAnimationCount()).c_str());

				Inspector::BeginField("Playback");
				if (ImGui::Button("Play"))
					comp->Play();
				ImGui::SameLine();
				if (ImGui::Button("Pause"))
					comp->Pause();
				Inspector::EndField();

				Inspector::EndComponent();
			},
			[](Entity& entity) { entity.AddComponent<AnimatedGraphicsComponent>(); }
		});

		registry.Register<PhysicsComponent>({
			"Physics",
			[](YAML::Emitter& emitter, IEntityComponent* component, Entity& entity)
			{
				using namespace YAML;
				auto* comp = static_cast<PhysicsComponent*>(component);
				emitter << BeginMap;
				emitter << Key << "PhysicsObjectType" << Value << static_cast<int>(comp->GetPhysicsType());
				WriteBodyDef(emitter, comp->GetBodyDef());
				emitter << Key << "Size" << Value << Flow << BeginSeq << comp->GetSize().x << comp->GetSize().y << EndSeq;
				emitter << Key << "Position" << Value << Flow << BeginSeq << comp->GetPosition().x << comp->GetPosition().y << EndSeq;
				emitter << Key << "Density" << Value << comp->GetDensity();
				WriteFixtureDef(emitter, comp->GetFixtureDef());
				emitter << EndMap;
			},
			[](const YAML::Node& node, Entity& entity)
			{
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

				entity.AddComponent<PhysicsComponent>(entity.GetEngine()->GetMainWorld(), objectType, bdef, fdef, size, position, density);
			},
			[](IEntityComponent* component, Editor& editor)
			{
				auto* comp = static_cast<PhysicsComponent*>(component);
				if (!Inspector::BeginComponent(component))
					return;

				static const char* typeNames[] = { "Chain", "Circle", "Edge", "Polygon" };
				b2FixtureDef fdef = comp->GetFixtureDef();
				Vec2 size = comp->GetSize();

				Inspector::LabeledText("Type", typeNames[static_cast<int>(comp->GetPhysicsType())]);
				Inspector::LabeledText("Size", (std::to_string((int)size.x) + " x " + std::to_string((int)size.y)).c_str());

				float density = comp->GetDensity();
				if (Inspector::DragFloat("Density", density, 1.0f, 0.01f))
					comp->SetDensity(density < 0.0f ? 0.0f : density);

				float friction = fdef.friction;
				if (Inspector::DragFloat("Friction", friction, 0.2f, 0.01f))
					comp->SetFriction(friction < 0.0f ? 0.0f : friction);

				float restitution = fdef.restitution;
				if (Inspector::DragFloat("Restitution", restitution, 0.0f, 0.01f))
					comp->SetRestitution(restitution < 0.0f ? 0.0f : restitution);

				Inspector::EndComponent();
			},
			[](Entity& entity) { b2BodyDef bdef; entity.AddComponent<PhysicsComponent>(entity.GetEngine()->GetMainWorld(), PhysicsObjectType::POLYGON, bdef); }
		});
	}
}
