#include "RectangleShape.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

RectangleShape::RectangleShape(sf::Vector2f size) {
	Drawable = new sf::RectangleShape(size);
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