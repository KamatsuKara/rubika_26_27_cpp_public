#pragma once

#include <string>
#include <type_traits>

#include "Logger.h"
#include "DebugMgr.h"

#include "IComponent.h"

#include "TransformComponent.h"
#include "RenderComponent.hpp"

namespace sf
{
	class RenderWindow;
}

class Entity : public IDebugable
{
public:
	Entity(std::string friendlyName = "");
	virtual ~Entity();

	void DrawDebug();

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();

	inline std::string GetFriendlyName() const { return friendlyName; }
	inline std::string GetUuid() const { return uuid; }

	template <typename C>
	C* AddComponent();

	template <typename C>
	C* GetComponent() const;

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
	std::vector<IComponent*> components;
};

template <typename C>
C* Entity::AddComponent() {
	if (!std::is_base_of<IComponent, C>::value) return nullptr;
	if (GetComponent<C>() != nullptr) {
		Logger::Warning("Trying to add the same component two time in Entity " + friendlyName);
		return nullptr;
	}
	C* c = new C(*this);
	components.push_back(c);
	return c;
}

template <typename C>
C* Entity::GetComponent() const {
	if (!std::is_base_of<IComponent, C>::value) return nullptr;
	for (IComponent* component : components) {
		C* c = dynamic_cast<C*>(component);
		if (c != nullptr) return c;
	}
	return nullptr;
}