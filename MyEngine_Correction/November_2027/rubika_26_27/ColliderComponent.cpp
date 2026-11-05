#include "ColliderComponent.h"
#include "Entity.h"

#include <Profiler.h>

#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transform.hpp>
#include "TransformComponent.h"
#endif

ColliderComponent::ColliderComponent(Entity& entity):IComponent(entity),active(true),IsTrigger(false),
maskMode(MaskMode::Flex),mask(Tags::Tag::None) {
	rect.size = sf::Vector2f(10, 10);
	rect.position = sf::Vector2f(0, 0);
#ifdef _USE_IMGUI
	displayColliderDebug = false;
#endif
}

ColliderComponent::~ColliderComponent() {

}

void ColliderComponent::Start() {

}

void ColliderComponent::Update(float fDeltaTime) {
	PROFILER_EVENT_BEGIN(PROFILER_COLOR_GREEN, "Update Collider");
	rect.position = offset + GetEntity().GetComponent<TransformComponent>()->GetWorldPosition();
	PROFILER_EVENT_END();
}

void ColliderComponent::Destroy() {

}

#ifdef _USE_IMGUI
void ColliderComponent::Draw(sf::RenderWindow& window) {
	if (!active || !displayColliderDebug) return;
	
	sf::RectangleShape visual(rect.size);
	visual.setFillColor(sf::Color::Transparent);
	visual.setOutlineThickness(3);
	visual.setOutlineColor(sf::Color::Magenta);

	sf::RenderStates states = sf::RenderStates::Default;
	states.transform = GetEntity().GetComponent<TransformComponent>()->GetMatrix();
	states.transform.translate(offset);

	window.draw(visual, states);
}
#endif

void ColliderComponent::OnCollisionCallback(ColliderComponent* otherCollider) {
	for (sCallbackInfo callbackInfo : Callbacks) {
		callbackInfo.Callback(&otherCollider->GetEntity());
	}
}

void ColliderComponent::DrawDebug()
{
#ifdef _USE_IMGUI
	if (ImGui::Checkbox("Active", &active))
	{}
	ImGui::SameLine();
	if (ImGui::Checkbox("Display Collider", &displayColliderDebug))
	{}
	ImGui::InputFloat2("Size", &rect.size.x);
	ImGui::InputFloat2("Offset", &rect.position.x);
#endif
}