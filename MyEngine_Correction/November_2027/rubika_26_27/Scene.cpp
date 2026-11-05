#include "Scene.h"

#include <Entity.h>
#include "ColliderComponent.h"

#include <Imgui/imgui.h>
#include <Profiler.h>

Scene::Scene(const std::string& name) : Name(name)
{
	Hash = std::hash<std::string>{}(Name);
}

Scene::~Scene()
{}

void Scene::Start()
{
	for (Entity* e : Entities)
	{
		e->Start();
	}
}

void Scene::Update(float fDeltaTime)
{
	PROFILER_EVENT_BEGIN(PROFILER_COLOR_BLACK, "Update Entity");
	for (Entity* e : Entities)
	{
		e->Update(fDeltaTime);
	}
	PROFILER_EVENT_END();


	PROFILER_EVENT_BEGIN(PROFILER_COLOR_GREEN, "Compute Collision");
	for (std::size_t i1 = 0; i1 < Entities.size(); ++i1)
	{
		if (ColliderComponent* colliderE1 = Entities[i1]->GetComponent<ColliderComponent>()) {
			for (std::size_t i2 = i1+1; i2 < Entities.size(); ++i2)
			{
				if (ColliderComponent* colliderE2 = Entities[i2]->GetComponent<ColliderComponent>()) {
					std::optional<sf::FloatRect> intersect = colliderE1->GetHitbox().findIntersection(colliderE2->GetHitbox());
					if (intersect.has_value()) {
						colliderE1->OnCollisionCallback(colliderE2);
						colliderE2->OnCollisionCallback(colliderE1);
					}
				}
			}
		}
	}
	PROFILER_EVENT_END();
}

void Scene::Destroy()
{
	for (Entity* e : Entities)
	{
		e->Destroy();
	}
}

void Scene::RemoveEntity(Entity* entity)
{
	for (auto it = Entities.begin(); it != Entities.end(); ++it)
	{
		if (entity == *it)
		{
			entity->Destroy();
			it = Entities.erase(it);
		}
	}
}

void Scene::UpdateCacheEntity(Entity* changedEntity) {
	for (int i = 0; i < StaticEntities.size(); ++i) {
		if (StaticEntities[i] = changedEntity) {
			StaticEntities.erase(StaticEntities.begin() + i);
			break;
		}
	}

	for (int i = 0; i < DynamicEntities.size(); ++i) {
		if (DynamicEntities[i] = changedEntity) {
			DynamicEntities.erase(DynamicEntities.begin() + i);
			break;
		}
	}

	if (changedEntity->HasTag(Tags::Tag::Static))
		StaticEntities.push_back(changedEntity);

	if (changedEntity->HasTag(Tags::Tag::Dynamic))
		DynamicEntities.push_back(changedEntity);
}

void Scene::Draw(sf::RenderWindow& window) const
{
	for (Entity* e : Entities)
	{
		e->Draw(window);
	}
}

void Scene::DrawDebug()
{
	for (Entity* e : Entities)
	{
		ImGui::PushID(e);

		const char* preview = e->GetName().size() ? e->GetName().c_str() : "Entity";
		if (ImGui::TreeNode(preview))
		{
			e->DrawDebug();
			ImGui::TreePop();
		}

		ImGui::PopID();
	}
}

