#pragma once

#include <string>
#include "DebugMgr.h"

class Entity;

class IComponent abstract : public IDebugable
{
public:
	IComponent() = delete;
	IComponent(Entity& entity):ParentEntity(entity){}

	virtual ~IComponent(){}

	virtual std::string GetName() = 0;

	virtual void Start() = 0;
	virtual void Update(float fDeltaTime) = 0;
	virtual void Destroy() = 0;

protected:
	Entity& GetEntity() const { return ParentEntity; };

private:
	Entity& ParentEntity;
};
