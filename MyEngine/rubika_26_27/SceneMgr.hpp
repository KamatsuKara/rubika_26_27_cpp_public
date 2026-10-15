#pragma once

#include <map>

#include "DebugMgr.h"
#include "Scene.h"

class SceneMgr : public IDebugable
{
public:
	SceneMgr();
	~SceneMgr();

	void Init();
	void Shut();

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();

	virtual void DrawDebug() override;

	Scene* AddScene(std::string);
	bool SetActiveScene(std::string);
	
	inline Scene* GetScene(std::string name) { return &scenes.find(name)->second; }

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window) const;

private:
	std::map<std::string, Scene> scenes;
	Scene* activeScene;
};