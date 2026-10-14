#pragma once

#include <string>
#include "TransformComponent.h"
#include "RenderComponent.hpp"

namespace sf
{
	class RenderWindow;
}

class Entity
{
public:
	Entity(std::string friendlyName = "");
	virtual ~Entity();

	TransformComponent transform;
	RenderComponent render;

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();

	inline std::string GetFriendlyName() const { return friendlyName; }
	inline std::string GetUuid() const { return uuid; }

	inline bool operator==(const Entity& entity) { return uuid == entity.GetUuid(); };
	inline bool operator!=(const Entity& entity) { return uuid != entity.GetUuid(); };

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window) const;
private:
	std::string friendlyName;
	std::string uuid;
};
