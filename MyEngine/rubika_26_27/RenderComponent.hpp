#pragma once

#include "IComponent.h"

class RenderComponent : public IComponent
{
public:
	RenderComponent(Entity&);
	~RenderComponent();

	void Start();
	void Update(float fDeltaTime);
	void Destroy();

private:
};
