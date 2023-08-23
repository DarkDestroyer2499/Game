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

	Scene::Scene(const Scene& other)
	{
		this->mEntityList = other.mEntityList;
		this->mEngine = other.mEngine;
		this->mName = other.mName;
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


