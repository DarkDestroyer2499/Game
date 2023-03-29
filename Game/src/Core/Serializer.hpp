#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP


#include "Core/Scene.hpp"
#include <fstream>
#include "yaml.h"
#include "Core/Engine.hpp"

namespace Oblivion
{
	class Serializer
	{
	public:
		Serializer(Engine* engine);
		Serializer(Engine* engine, Scene& scene);


		void Serialize(Scene& scene, ::std::filesystem::path filePath);
		bool Deserialize(Scene& scene, ::std::filesystem::path filePath);

	private:
		void Serialize(Entity& entity);
		void Serialize(b2BodyDef bdef);
		void Serialize(b2FixtureDef fdef);

		void Deserialize(Entity& entity);
		b2BodyDef DeserializeBodyDef(YAML::Node& data);
		b2FixtureDef DeserializeFixtureDef(YAML::Node& data);
	private:
		Engine* mEngine;
		::std::ofstream mStream;
		YAML::Emitter mEmitter;
	};
}
#endif // !SERIALIZER_HPP
