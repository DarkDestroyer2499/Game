#include "Font.hpp"

namespace Oblivion
{
	FontComponent::FontComponent(Editor* editor)
		: mEditor{ editor }, mIO{ ImGui::GetIO() }
	{
	}
	void FontComponent::AddFont(const char* pathToFont, const char* fontName, float fontSize, ImFontConfig config = ImFontConfig(), ImWchar* ranges = nullptr)
	{
		mFonts[fontName] = mIO.Fonts->AddFontFromFileTTF(pathToFont, fontSize, &config, ranges);
	}

	ImFont* FontComponent::GetFont(const char* fontName)
	{
		if (mFonts.find(fontName) == mFonts.end()) {
			// not found
			return nullptr;
		}
		else {
			// found
			return mFonts[fontName];
		}
	}

	bool FontComponent::HasFont(const char* fontName)
	{
		if (mFonts.find(fontName) == mFonts.end()) {
			return false;
		}
		else {
			return true;
		}
	}

	void FontComponent::Update()
	{
	}
}