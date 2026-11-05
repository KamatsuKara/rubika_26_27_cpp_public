#pragma once

#include <SFML/System/Vector2.hpp>
#include <map>
#include <vector>

#include "Entity.h"

class GridEntityCache {
public:
	GridEntityCache(sf::Vector2i, sf::Vector2i);

private:
	std::map<sf::Vector2i, std::vector<Entity*>> grid;

	sf::Vector2i gridRange;
	sf::Vector2i cellSize;
};