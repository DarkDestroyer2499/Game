#ifndef I_COMPONENT_H
#define I_COMPONENT_H

#include <string>

#define COMPONENT_NAME (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1)).substr(0, (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1)).find_first_of('.'))

//std::string tmp = std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1);
//std::cout << "Name: " << tmp.substr(0, tmp.find_last_of('.')) << std::endl;

class Entity;

class IComponent
{
public:
	virtual void Update() = 0;
	virtual void SetOwner(Entity* newOwner) { mOwner = newOwner; }
	virtual const char* GetName() = 0;
	virtual ~IComponent() {};
protected:
	Entity* mOwner;
	std::string mName;
};

#endif // !I_COMPONENT_H
