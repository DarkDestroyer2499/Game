#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "../Engine.hpp"
#include "../Util/Util.hpp"
#include "UIVisualSelector.h"
#include "Components/UIComponents.hpp"
#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui-SFML.h"

constexpr const char* PROGRAM_NAME = "Engine";
static const sf::Color EDITOR_BG_COLOR(62, 66, 63);

struct SelectedObject
{
	Entity& entity;
	UIVisualSelector selector;
};

class Editor
{
public:
	Editor(sf::RenderTexture*, Engine&);
	Editor(Editor&&) = delete;
	Editor(Editor&) = delete;
	~Editor();

	Vec2 WindowToViewportCoords(const Vec2 &windowCoords);
	void Run();

	template<typename Component>
	bool HasComponent()
	{
		for (auto& component : mComponentList)
		{
			if (dynamic_cast<Component*>(component))
				return true;
		}
		return false;
	}

	template<typename Component>
	Component* GetComponent()
	{
		for (auto& component : mComponentList)
		{
			Component* tmp = dynamic_cast<Component*>(component);
			if (tmp)
				return tmp;
		}
		return nullptr;
	}

	template<typename Component, typename... Args>
	Component* AddComponent(Args&&... args)
	{
		Component* tmp = new Component(args...);
		mComponentList.push_back(tmp);
		return tmp;
	}

	template<typename Component>
	void RemoveComponent()
	{
		Component* tmpComponent = this->GetComponent<Component>();
		if (tmpComponent != nullptr)
		{
			this->mComponentList.erase(std::remove(this->mComponentList.begin(), this->mComponentList.end(), tmpComponent), this->mComponentList.end());
			delete tmpComponent;
		}
	}

private:
	bool IsAlreadySelected(Entity& entity);
	void EventHandler();

private:
	sf::RenderWindow mWindow;
	sf::Clock mClock;
	sf::Event mEvent;
	sf::RenderTexture* mTexture;
	Engine& mEngine;
	sf::Vector2i mMousePosition;
	std::vector<SelectedObject> mSelectedObjects;
	std::vector<IUIComponent*> mComponentList;

	friend class HierarchyComponent;
	friend class ViewportComponent;
};

#endif // !EDITOR_H
