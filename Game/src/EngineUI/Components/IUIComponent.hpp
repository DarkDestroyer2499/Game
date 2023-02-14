#ifndef IUI_COMPONENT_H
#define IUI_COMPONENT_H

class IUIComponent
{
public:
	virtual ~IUIComponent() = default;
	virtual void Update() = 0;
};

#endif // !IUI_COMPONENT_H
