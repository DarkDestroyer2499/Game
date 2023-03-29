#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "Entity.hpp"

namespace Oblivion
{
	
	class Engine;

	class Scene
	{
	public:
		Scene();
		Scene(Engine* engine, std::string name = "uknown scene");
		//TODO: Implement this
		//Scene(const Scene& other);
		//Scene(Scene&& other);
		::std::list<Entity>& GetEntityList();

		void SetName(std::string newName);
		::std::string GetName();

	private:
		::std::list<Entity> mEntityList;
		Engine* mEngine;
		::std::string mName;
	};
}
#endif // !SCENE_HPP
