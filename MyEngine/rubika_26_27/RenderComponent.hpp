#pragma once

#include "IComponent.h"
#include "IDrawable.h"

class RenderComponent : public IComponent
{
public:
	RenderComponent(Entity&);
	~RenderComponent();

	void DrawDebug();
	inline std::string GetName() { return "Render"; }

	void Start();
	void Update(float fDeltaTime);
	void Destroy();

	void Draw(sf::RenderWindow&) const;

	template <typename D>
	D* AddDrawable();

private:
	std::vector<IDrawable*> drawables;
};

template <typename D>
D* RenderComponent::AddDrawable() {
	if (!std::is_base_of<IDrawable, D>::value) return nullptr;
	D* d = new D();
	drawables.push_back(d);
	d->Start();
	return d;
}