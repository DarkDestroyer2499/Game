#ifndef I_COMPONENT_H
#define I_COMPONENT_H

class Entity;

class IComponent
{
public:
	virtual void Update() = 0;
	virtual void SetOwner(Entity* newOwner) { mOwner = newOwner; }
	virtual ~IComponent() {};
protected:
	Entity* mOwner;
};

#endif // !I_COMPONENT_H
