#pragma once

#include <string>
#include <vector>

class Entity;

namespace sf
{
	class RenderWindow;
}

class Scene
{
public:

	Scene(const std::string& name);
	~Scene();

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();

	template <typename E>
	E* CreateEntity(const std::string& entityName);
	void RemoveEntity(Entity* entity);
	
	void UpdateCacheEntity(Entity* changedEntity);

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window) const;
	void DrawDebug();

	const std::string& GetName() const { return Name; }
	std::size_t GetHash() const { return Hash; }


protected:

	std::string Name;
	std::size_t Hash;
	std::vector<Entity*> Entities;

	std::vector<Entity*> StaticEntities;
	std::vector<Entity*> DynamicEntities;
};

#include "Scene.hxx"