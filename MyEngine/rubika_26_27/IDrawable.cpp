#include "IDrawable.h"

IDrawable::IDrawable() : Visible(true), WorldTransform(sf::Transform::Identity), Drawable(nullptr)
{}

IDrawable::~IDrawable()
{}

bool IDrawable::IsVisible() const
{
	return Visible;
}

void IDrawable::SetVisibility(bool visible)
{
	Visible = visible;
}

const sf::Transform& IDrawable::GetWorldTransform() const
{
	return WorldTransform;
}

void IDrawable::SetWorldTransform(const sf::Transform& transform)
{
	WorldTransform = transform;
}

void IDrawable::SetOffset(sf::Vector2f newOffset)
{
	offset = newOffset;
}

sf::Vector2f IDrawable::GetOffset() const
{
	return offset;
}

void IDrawable::Draw(sf::RenderWindow& window) const
{
	if (!Drawable)
	{
		return;
	}

	sf::RenderStates states = sf::RenderStates::Default;
	states.transform = WorldTransform;
	states.transform.translate(offset);

	window.draw(*Drawable, states);
}
