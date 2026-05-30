#ifndef YAML_CONVERTERS_HPP
#define YAML_CONVERTERS_HPP

#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "yaml.h"
#include "Util/Util.hpp"

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

	inline Emitter& operator<<(Emitter& out, const sf::IntRect& rect)
	{
		out << Flow << BeginSeq << rect.left << rect.top << rect.width << rect.height << EndSeq;
		return out;
	}

	inline Emitter& operator<<(Emitter& out, const b2Vec2& rect)
	{
		out << Flow << BeginSeq << rect.x << rect.y << EndSeq;
		return out;
	}

	inline Emitter& operator<<(Emitter& out, const b2BodyType& type)
	{
		out << static_cast<int>(type);
		return out;
	}

	inline Emitter& operator<<(Emitter& out, const Oblivion::Vec2& rect)
	{
		out << Flow << BeginSeq << rect.x << rect.y << EndSeq;
		return out;
	}
}
#endif // !YAML_CONVERTERS_HPP
