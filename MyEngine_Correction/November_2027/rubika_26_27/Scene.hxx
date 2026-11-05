#pragma once

#include "Entity.h"

template <typename E>
inline E* Scene::CreateEntity(const std::string& entityName)
{
	if (!std::is_base_of<Entity, E>())
		return nullptr;

	E* e = new E(entityName);
	Entities.push_back(e);
	UpdateCacheEntity(e);
	return e;
}