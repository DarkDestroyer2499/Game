#ifndef I_COMPONENT_H
#define I_COMPONENT_H

#include <string>

#define COMPONENT_NAME (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1)).substr(0, (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1)).find_first_of('.'))

class Entity;

class IComponent
{
public:
	virtual ~IComponent() {};
	virtual void Update() = 0;
	virtual void SetOwner(Entity* newOwner) { mOwner = newOwner; }
	virtual const char* GetName() = 0;
protected:
	Entity* mOwner;
	std::string mName;	
	friend class Entity;
};

#endif // !I_COMPONENT_H
