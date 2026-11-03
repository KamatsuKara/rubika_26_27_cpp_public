#pragma once

#include <IComponent.h>

#include <SFML/Graphics/Transform.hpp>

class MovementComponent : public IComponent
{
public:
	MovementComponent(Entity& entity);

	void Start();
	void Update(float fDeltaTime);
	void Destroy();

	const char* GetName() const override { return "MovementComponent"; }
	void DrawDebug() override;

	inline void SetDirection(sf::Vector2f dir) { direction = dir; }
	inline sf::Vector2f GetDirection() { return direction; }

	inline void SetSpeed(float newSpeed) { speed = newSpeed; }
	inline float GetSpeed() { return speed; }

private:
	sf::Vector2f direction;
	float speed;
};
