#include "PhysicComponent.hpp"

#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif

#include "Globals.h"
#include "Logger.h"

#include "Entity.h"
#include "ICallEvent.hpp"
#include "ColliderComponent.h"
#include "TransformComponent.h"

PhysicComponent::PhysicComponent(Entity& entity) :IComponent(entity),IsStatic(false),mass(1){
	if (ColliderComponent* c = GetEntity().GetComponent<ColliderComponent>()) {
		c->RegisterCallback("Collide",
			[this](Entity* other){
				this->Collide(other);
			},
			this);
	}
	else
		gData.Logger->Error("trying to add a Physic Component Without a Collider Componement on a Entity");

	oldPos = GetEntity().GetComponent<TransformComponent>()->GetWorldPosition();
	velocity = sf::Vector2f(0, 0);
}

PhysicComponent::~PhysicComponent() {

}

void PhysicComponent::Start() {

}

void PhysicComponent::Update(float fDeltaTime) {
	velocity = GetEntity().GetComponent<TransformComponent>()->GetWorldPosition() - oldPos;
	oldPos = GetEntity().GetComponent<TransformComponent>()->GetWorldPosition();
}

void PhysicComponent::Destroy() {

}

void PhysicComponent::Collide(Entity* other) {
	if (other->GetComponent<ColliderComponent>()->GetIsTrigger()) return;
	if (other->GetComponent<PhysicComponent>()) {

	}
	else {
		GetEntity().GetComponent<TransformComponent>()->SetWorldPosition(
			GetEntity().GetComponent<TransformComponent>()->GetWorldPosition()
			- velocity
		);
		oldPos = GetEntity().GetComponent<TransformComponent>()->GetWorldPosition();
}
}

void PhysicComponent::DrawDebug()
{
#ifdef _USE_IMGUI
	ImGui::InputFloat2("Velocity", &velocity.x);
#endif
}