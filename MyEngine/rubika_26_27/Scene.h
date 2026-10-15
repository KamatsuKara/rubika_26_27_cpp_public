#pragma once

#include <string>
#include <vector>

#include "DebugMgr.h"
#include "Entity.h"

namespace sf
{
	class RenderWindow;
}

class Scene : public IDebugable
{
public:

	Scene(const std::string& name);
	~Scene();

	void DrawDebug();

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();

	Entity* AddEntity(std::string);
	void RemoveEntity(std::string);

	inline std::string GetName() const { return name; }
	inline int GetNmbEntity() const { return entities.size(); }
	inline Entity* GetEntity(int i) const { return entities[i]; }

	Entity* GetEntityByUuid(std::string);
	Entity* GetEntityByName(std::string);

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window) const;

private:
	std::vector<Entity*> entities;
	std::string name;

};