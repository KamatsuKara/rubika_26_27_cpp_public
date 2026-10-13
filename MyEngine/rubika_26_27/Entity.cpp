#include "Entity.h"
#include "uuid.hpp"

Entity::Entity(std::string friendlyName):friendlyName(friendlyName) {
	transform = TransformComponent();
	uuid = uuid::generate_uuid();
}

Entity::~Entity() {

}

void Entity::Start() {

}

void Entity::Update(float fDeltaTime) {

}

void Entity::Destroy() {

}

void Entity::Draw(sf::RenderWindow& window) const {

}