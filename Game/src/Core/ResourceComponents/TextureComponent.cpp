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
		if (mTexture.find(path.string()) != mTexture.end()) {
			Log(ERROR, "Texture already exists!: " << path);
			return nullptr;
		}

		sf::Texture tmp;
		if (!tmp.loadFromFile(path.string()))
		{
			Log(ERROR, "Wrong path: " << path);
			return nullptr;
		}

		mTexture[path.string()] = tmp;
		return &mTexture[path.string()];
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
