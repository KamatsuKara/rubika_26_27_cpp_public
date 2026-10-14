#include "Sprite.hpp"

#include <SFML/Graphics/Sprite.hpp>

Sprite::Sprite(const sf::Texture& texture) {
	Drawable = new sf::Sprite(texture);
}


void Sprite::Start()
{
}

void Sprite::Update(float fDeltaTime)
{
}

void Sprite::Destroy()
{
}