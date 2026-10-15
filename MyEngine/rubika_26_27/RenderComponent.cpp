#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif

#include "RenderComponent.hpp"
#include "Entity.h"

RenderComponent::RenderComponent(Entity& parent): IComponent(parent) {

}

RenderComponent::~RenderComponent() {
	for (IDrawable* drawable : drawables)
		delete drawable;
}

void RenderComponent::Start(){
	for (IDrawable* drawable : drawables)
		drawable->Start();
}

void RenderComponent::Update(float fDeltaTime){
	for (IDrawable* drawable : drawables) {
		drawable->SetWorldTransform(GetEntity().GetComponent<TransformComponent>()->GetMatrix());
		drawable->Update(fDeltaTime);
	}
}

void RenderComponent::Destroy(){
	for (IDrawable* drawable : drawables)
		drawable->Destroy();
}

void RenderComponent::Draw(sf::RenderWindow& window) const {
	for (IDrawable* drawable : drawables)
		drawable->Draw(window);
}


void RenderComponent::DrawDebug() {
#ifdef _USE_IMGUI
	ImGui::Text(("Number of Drawable : " + std::to_string(drawables.size())).c_str());
#endif
}