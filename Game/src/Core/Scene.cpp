#include "Scene.hpp"

namespace Oblivion
{
	Scene::Scene() :
		mEngine{ nullptr }, mName{}
	{
	}

	Scene::Scene(Engine* engine, std::string sceneName)
		: mEngine{ engine }, mName{ sceneName }
	{
	}

	::std::list<Entity>& Oblivion::Scene::GetEntityList()
	{
		return mEntityList;
	}

	void Scene::SetName(std::string newName)
	{
		mName = newName;
	}

	::std::string Scene::GetName()
	{
		return mName;
	}
}


