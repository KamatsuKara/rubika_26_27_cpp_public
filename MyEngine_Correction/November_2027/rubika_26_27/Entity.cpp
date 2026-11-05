#include "Entity.h"

#include "Globals.h"
#include "SceneMgr.h"
#include "Scene.h"

#include <IComponent.h>
#include <RenderComponent.h>
#include <ColliderComponent.h>
#include <Imgui/imgui.h>


Entity::Entity(std::string friendlyName) : FriendlyName(friendlyName), tags(Tags::Tag::None)
{}

Entity::~Entity()
{
	for (const IComponent* component : Components)
	{
		delete component;
	}

	Components.clear();
}

void Entity::Start()
{
	for (IComponent* c : Components)
	{
		c->Start();
	}
}

void Entity::Update(float fDeltaTime)
{
	for (IComponent* c : Components)
	{
		c->Update(fDeltaTime);
	}
}

void Entity::Destroy()
{
	for (IComponent* c : Components)
	{
		c->Destroy();
	}
}

void Entity::AddTag(Tags::Tag tag) {
	tags |= tag;
	gData.SceneMgr->GetActiveScene()->UpdateCacheEntity(this);
}

void Entity::RemoveTag(Tags::Tag tag) {
	tags &= ~tag;
	gData.SceneMgr->GetActiveScene()->UpdateCacheEntity(this);
}

bool Entity::HasTag(Tags::Tag tag) {
	return ((tags & tag) == tag);
}

bool Entity::HasAtLeastOneTag(Tags::Tag tag) {
	return ((tags & tag) != 0);
}

void Entity::Draw(sf::RenderWindow& window) const
{
	RenderComponent* r = GetComponent<RenderComponent>();
	if (r)
	{
		r->Draw(window);
	}
#ifdef _USE_IMGUI
	ColliderComponent* c = GetComponent<ColliderComponent>();
	if (c)
	{
		c->Draw(window);
	}
#endif
}

void Entity::DrawDebug()
{
#ifdef _USE_IMGUI
	for (IComponent* c : Components)
	{
		if (ImGui::TreeNode(c->GetName()))
		{
			c->DrawDebug();
			ImGui::TreePop();
		}
	}
#endif
}
