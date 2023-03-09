#ifndef FONT_H
#define FONT_H

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

namespace Oblivion
{
	class FontComponent : public IEditorComponent
	{
	public:
		FontComponent(Editor*);
		~FontComponent() = default;

		void AddFont(const char* pathToFont, const char* fontName, float size, ImFontConfig config, ImWchar* ranges);

		ImFont* GetFont(const char*);
		bool HasFont(const char*);
		void Update() override;
	private:
		Editor* mEditor;
		::std::map<::std::string, ImFont*> mFonts;
		ImGuiIO& mIO;
	};
}
#endif // !FONT_H
