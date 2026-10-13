#include "Scene.h"

Scene::Scene(const std::string& name):name(name) {
	entities = {};
}

Scene::~Scene() {
}

void Scene::Start() {
	for (Entity* entity : entities) {
		entity->Start();
	}
}

void Scene::Update(float fDeltaTime) {
	for (Entity* entity : entities) {
		entity->Update(fDeltaTime);
	}
}

void Scene::Destroy() {
	for (Entity* entity : entities) {
		entity->Destroy();
	}
}

Entity* Scene::AddEntity(std::string friendlyName) {
	entities.push_back(new Entity(friendlyName));
	return entities[entities.size()-1];
}

void Scene::RemoveEntity(std::string uuid) {
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->GetUuid() == uuid) {
			entities.erase(entities.begin() + i);
			return;
		}
	}
}

Entity* Scene::GetEntityByUuid(std::string uuid) {
	for (Entity* entity : entities) {
		if (entity->GetUuid() == uuid)
			return entity;
	}
	return nullptr;
}

Entity* Scene::GetEntityByName(std::string name) {
	for (Entity* entity : entities) {
		if (entity->GetFriendlyName() == name)
			return entity;
	}
	return nullptr;
}

void Scene::Draw(sf::RenderWindow& window) const {
	for (Entity* entity : entities) {
		entity->Draw(window);
	}
}