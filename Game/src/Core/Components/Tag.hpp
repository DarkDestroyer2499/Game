#ifndef TAG_H
#define TAG_H

#include "IEntityComponent.hpp"

namespace Oblivion
{
	class TagComponent : public IEntityComponent
	{
	public:
		TagComponent() = delete;
		TagComponent(const ::std::string& newTag);
		~TagComponent();

		void Update(const float&) override;
		void SetTag(::std::string& newTag);
		void SetTag(::std::string newTag);
		void SetTag(char* newTag);
		const ::std::string& GetTag() const;
	private:
		::std::string mTag;
	};
}
#endif // !TAG_H
