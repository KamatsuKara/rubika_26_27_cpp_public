#include "MovementComponent.hpp"
#include "TransformComponent.h"
#include "Entity.h"

#include <Imgui/imgui.h>

MovementComponent::MovementComponent(Entity& entity) : IComponent(entity)
{
	direction = sf::Vector2f(0, 0);
	speed = 1;
}

void MovementComponent::Start()
{
}

void MovementComponent::Update(float fDeltaTime)
{
	if (direction == sf::Vector2f(0, 0)) return;
	GetEntity().GetComponent<TransformComponent>()->SetWorldPosition(
		GetEntity().GetComponent<TransformComponent>()->GetWorldPosition() +
		(direction.normalized() * speed * fDeltaTime)
	);
}

void MovementComponent::Destroy()
{
}

void MovementComponent::DrawDebug()
{
#ifdef _USE_IMGUI
	ImGui::SliderFloat("Speed", &speed, 0, 500);
#endif
}
