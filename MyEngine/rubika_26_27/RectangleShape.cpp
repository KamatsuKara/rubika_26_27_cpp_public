#include "RectangleShape.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

RectangleShape::RectangleShape() {
	Drawable = new sf::RectangleShape(sf::Vector2f(50,50));
	WorldTransform = sf::Transform();
	
}

void RectangleShape::setFillColor(sf::Color color) {
	sf::RectangleShape* rect = static_cast<sf::RectangleShape*>(Drawable);
	rect->setFillColor(color);
}

void RectangleShape::Start()
{
}

void RectangleShape::Update(float fDeltaTime)
{
}

void RectangleShape::Destroy()
{
}