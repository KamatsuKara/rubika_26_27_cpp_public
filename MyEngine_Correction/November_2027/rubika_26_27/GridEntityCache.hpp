#pragma once

#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <map>
#include <vector>

#include "Entity.h"

class GridEntityCache {
public:
	GridEntityCache(sf::Vector2i, sf::Vector2i);

	void AddEntity(Entity*);
	void RemoveEntity(Entity*);

	void GetEntities(sf::Vector2i, std::vector<Entity*>&);
	void GetEntities(sf::Vector2i, sf::Vector2i, std::vector<Entity*>&);

	void UpdatePosEntity(sf::Vector2i, sf::Vector2i, Entity*);
private:
	sf::Vector2i WorldPosToCellPos(sf::Vector2i);

	std::map<sf::Vector2i, std::vector<Entity*>> grid;

	sf::Vector2i gridRange;
	sf::Vector2i cellSize;
};