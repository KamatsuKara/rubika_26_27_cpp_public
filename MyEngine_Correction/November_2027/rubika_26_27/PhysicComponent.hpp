#pragma once

#include "IComponent.h"
#include <SFML/System/Vector2.hpp>

class PhysicComponent : public IComponent
{
public:
	PhysicComponent(Entity& entity);
	~PhysicComponent();

	virtual void Start() override;
	virtual void Update(float fDeltaTime) override;
	virtual void Destroy() override;

	inline void SetIsStatic(bool isStatic) { IsStatic = isStatic; }
	inline bool GetIsStatic() { return IsStatic; }

	const char* GetName() const override { return "PhysicComponent"; }
	void DrawDebug() override;

private:
	bool IsStatic;
	float mass;

	sf::Vector2f oldPos;
	sf::Vector2f velocity;

	void Collide(Entity* other);

};