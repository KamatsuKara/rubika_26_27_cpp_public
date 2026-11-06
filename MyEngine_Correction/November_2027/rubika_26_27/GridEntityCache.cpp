#include "GridEntityCache.hpp"

#include "TransformComponent.h"
#include "ColliderComponent.h"

#include <SfML/Graphics/Rect.hpp>

GridEntityCache::GridEntityCache(sf::Vector2i range, sf::Vector2i size) :gridRange(range), cellSize(size) {

}

sf::Vector2i GridEntityCache::WorldPosToCellPos(sf::Vector2i worldPos) {
	if (worldPos.x < 0 || worldPos.y < 0) return sf::Vector2i(0, 0);
	if (worldPos.x > gridRange.x || worldPos.y > gridRange.y) return sf::Vector2i(0, 0);

	return sf::Vector2i(floor(worldPos.x / cellSize.x), floor(worldPos.y % cellSize.y));
}

void GridEntityCache::AddEntity(Entity* entity) {
	if (ColliderComponent* collider = entity->GetComponent<ColliderComponent>()) {
		sf::Vector2f position = collider->GetHitbox().position;
		sf::Vector2f size = collider->GetHitbox().size;
		sf::Vector2i minPos = WorldPosToCellPos(sf::Vector2i(floor(position.x - (size.x)), floor(position.y - (size.y))));
		sf::Vector2i maxPos = WorldPosToCellPos(sf::Vector2i(floor(position.x + (size.x)), floor(position.y + (size.y))));
		for (int x = minPos.x; x <= maxPos.x; x++) {
			for (int y = minPos.y; x <= maxPos.y; y++) {
				grid[sf::Vector2i(x,y)].push_back(entity);
			}
		}
	}
	else {
		sf::Vector2f worldPos = entity->GetComponent<TransformComponent>()->GetWorldPosition();
		sf::Vector2i pos = WorldPosToCellPos(sf::Vector2i(floor(worldPos.x), floor(worldPos.y)));
		grid[pos].push_back(entity);
	}
}
void GridEntityCache::RemoveEntity(Entity* entity) {
	if (ColliderComponent* collider = entity->GetComponent<ColliderComponent>()) {
		sf::Vector2f position = collider->GetHitbox().position;
		sf::Vector2f size = collider->GetHitbox().size;
		sf::Vector2i minPos = WorldPosToCellPos(sf::Vector2i(floor(position.x - (size.x)), floor(position.y - (size.y))));
		sf::Vector2i maxPos = WorldPosToCellPos(sf::Vector2i(floor(position.x + (size.x)), floor(position.y + (size.y))));
		for (int x = minPos.x; x <= maxPos.x; x++) {
			for (int y = minPos.y; x <= maxPos.y; y++) {
				sf::Vector2i pos(x, y);
				for (int i = 0; i < grid[pos].size(); i++) {
					if (grid[pos][i] == entity) {
						grid[pos].erase(grid[pos].begin() + i);
						break;
					}
				}
			}
		}
	}
	else {
		sf::Vector2f worldPos = entity->GetComponent<TransformComponent>()->GetWorldPosition();
		sf::Vector2i pos = WorldPosToCellPos(sf::Vector2i(floor(worldPos.x), floor(worldPos.y)));
		
		for (int i = 0; i < grid[pos].size(); i++) {
			if (grid[pos][i] == entity) {
				grid[pos].erase(grid[pos].begin() + i);
				break;
			}
		}
	}
}

void GridEntityCache::GetEntities(sf::Vector2i pos, std::vector<Entity*>& entities) {
	for (Entity* e : grid[WorldPosToCellPos(pos)]) {
		entities.push_back(e);
	}
}

void GridEntityCache::GetEntities(sf::Vector2i pos, sf::Vector2i size, std::vector<Entity*>& entities) {
	sf::Vector2i minPos = WorldPosToCellPos(sf::Vector2i(pos.x - (size.x), pos.y - (size.y)));
	sf::Vector2i maxPos = WorldPosToCellPos(sf::Vector2i(pos.x + (size.x), pos.y + (size.y)));
	for (int x = minPos.x; x <= maxPos.x; x++) {
		for (int y = minPos.y; x <= maxPos.y; y++) {
			sf::Vector2i pos(x, y);
			for (Entity* e : grid[pos]) {
				entities.push_back(e);
			}
		}
	}
}

void UpdatePosEntity(sf::Vector2i oldPos, sf::Vector2i newPos, Entity* entity) {
	if (ColliderComponent* collider = entity->GetComponent<ColliderComponent>()) {
		sf::Vector2f offset = collider->GetHitboxOffset();
		sf::Vector2f size = collider->GetHitbox().size;

		//sf::Vector2i oldMinPos = WorldPosToCellPos(sf::Vector2i(oldPos.x + offset.x - (size.x), oldPos.y + offset.y - (size.y)));
		//sf::Vector2i oldMaxPos = WorldPosToCellPos(sf::Vector2i(oldPos.x + offset.y + (size.x), oldPos.y + offset.y + (size.y)));
	}
}