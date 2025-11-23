#ifndef TEXTURE_COMPONENT_HPP
#define TEXTURE_COMPONENT_HPP

#include <filesystem>
#include "SFML/Graphics.hpp"
#include "IResourceComponent.hpp"
#include <map>

namespace Oblivion
{
	class TextureComponent : public IResourceComponent
	{
	public:
		COMPONENT_TYPE_IMPL(TextureComponent)
		TextureComponent();
		virtual ~TextureComponent() = default;

		sf::Texture* AddTexture(::std::filesystem::path path);

		::std::string GetTexturePath(const sf::Texture* texture);

		sf::Texture* GetTexture(::std::string name);

	private:
		::std::map<::std::string, sf::Texture> mTexture;
	};
}
#endif // !TEXTURE_COMPONENT_HPP
