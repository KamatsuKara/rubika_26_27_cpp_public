#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif

#include "TransformComponent.h"

TransformComponent::TransformComponent(Entity& parent):IComponent(parent)
{
	WorldPosition = sf::Vector2f();
	WorldPositionQuery = sf::Vector2f();
	Rotation = 0.f;
	Scale = sf::Vector2f(1.f, 1.f);

	UpdateMatrix();
}


TransformComponent::~TransformComponent()
{
}

const sf::Transform& TransformComponent::GetMatrix() const
{
	return Matrix;
}

void TransformComponent::SetWorldPosition(sf::Vector2f newPosition)
{
	WorldPosition = newPosition;
	WorldPositionQuery = newPosition;
	UpdateMatrix();
}

sf::Vector2f TransformComponent::GetWorldPosition() const
{
	return WorldPosition;
}

void TransformComponent::SetWorldPositionQuery(sf::Vector2f newPosition)
{
	WorldPositionQuery = newPosition;
}

sf::Vector2f TransformComponent::GetWorldPositionQuery() const
{
	return WorldPositionQuery;
}

void TransformComponent::SetRotation(float newRotation)
{
	Rotation = newRotation;
	UpdateMatrix();
}

float TransformComponent::GetRotation() const
{
	return Rotation;
}

void TransformComponent::SetScale(sf::Vector2f newScale)
{
	Scale = newScale;
	UpdateMatrix();
}

sf::Vector2f TransformComponent::GetScale() const
{
	return Scale;
}

void TransformComponent::Start()
{}

void TransformComponent::Update(float fDeltaTime)
{}

void TransformComponent::Destroy()
{}

void TransformComponent::UpdateMatrix()
{
	Matrix = sf::Transform::Identity;
	Matrix.translate(WorldPosition);
	Matrix.rotate(sf::degrees(Rotation));
	Matrix.scale(Scale);
}


void TransformComponent::DrawDebug() {
#ifdef _USE_IMGUI
	float vec2Pos[2] = { WorldPosition.x, WorldPosition.y};
	ImGui::InputFloat2("World Position", vec2Pos);
	SetWorldPosition(sf::Vector2f(vec2Pos[0], vec2Pos[1]));

	float rot[1] = { Rotation };
	ImGui::InputFloat("Rotation", rot);
	SetRotation(rot[0]);

	float vec2Scale[2] = { Scale.x, Scale.y };
	ImGui::InputFloat2("Scale", vec2Scale);
	SetScale(sf::Vector2f(vec2Scale[0], vec2Scale[1]));

#endif
}