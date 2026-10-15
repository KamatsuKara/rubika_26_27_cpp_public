#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif

#include "Entity.h"
#include "uuid.hpp"

Entity::Entity(std::string friendlyName):friendlyName(friendlyName) {
	uuid = uuid::generate_uuid();
}

Entity::~Entity() {

}

void Entity::Start() {
	for (IComponent* component : components)
		component->Start();
}

void Entity::Update(float fDeltaTime) {
	for (IComponent* component : components)
		component->Update(fDeltaTime);
}

void Entity::Destroy() {
	for (IComponent* component : components)
		component->Destroy();
}

void Entity::Draw(sf::RenderWindow& window) const {
	RenderComponent* render = GetComponent<RenderComponent>();
	if (render != nullptr)
		render->Draw(window);
}

void Entity::DrawDebug() {
#ifdef _USE_IMGUI
	for (IComponent* component : components) {
		bool isOpen = ImGui::TreeNode(component->GetName().c_str());
		if (isOpen)
		{
			component->DrawDebug();
			ImGui::TreePop();
		}
	}
#endif
}