#include "TextureComponent.hpp"
#include "Util/Log.hpp"

namespace Oblivion
{
	TextureComponent::TextureComponent()
	{
		mName = COMPONENT_NAME;
	}
	sf::Texture* TextureComponent::AddTexture(::std::filesystem::path path)
	{
		const std::string key = path.string();

		if (mTexture.find(key) != mTexture.end()) {
			Log(ERROR, "Texture already exists!: " << path);
			return nullptr;
		}

		sf::Texture& tex = mTexture[key];
		if (!tex.loadFromFile(key))
		{
			Log(ERROR, "Wrong path: " << path);
			mTexture.erase(key);
			return nullptr;
		}

		return &tex;
	}

	sf::Texture* TextureComponent::GetOrLoadTexture(::std::filesystem::path path)
	{
		if (sf::Texture* existing = GetTexture(path.string()))
			return existing;
		return AddTexture(path);
	}

	::std::string TextureComponent::GetTexturePath(const sf::Texture* textureToFind)
	{
		for (const auto& [key, texture] : mTexture) {
			if (&(*textureToFind) == &texture)
			{
				return key;
			}
		}

		return "";
	}

	sf::Texture* TextureComponent::GetTexture(::std::string name)
	{
		if (mTexture.find(name) == mTexture.end()) {
			return nullptr;
		}

		return &mTexture[name];
	}
}
