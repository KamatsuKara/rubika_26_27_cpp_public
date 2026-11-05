#pragma once

#include <IComponent.h>

#include <SfML/Graphics/Rect.hpp>
#include <functional>

#include "ICallEvent.hpp"

#ifdef _USE_IMGUI
#include <SFML/Graphics/RenderWindow.hpp>
#endif

class ColliderComponent : public IComponent, public ICallEvent<std::function<void(Entity*)>>
{
public:
	ColliderComponent(Entity& entity);
	~ColliderComponent();

	virtual void Start() override;
	virtual void Update(float fDeltaTime) override;
	virtual void Destroy() override;

#ifdef _USE_IMGUI
	void Draw(sf::RenderWindow& window);
#endif

	const char* GetName() const override { return "ColliderComponent"; }
	void DrawDebug() override;

	inline void SetHitboxSize(sf::Vector2f size) { rect.size = size; }
	inline void SetHitboxOffset(sf::Vector2f newOffset) { offset = newOffset; }

	inline void EnableCollision(bool enable) { active = enable; }
	inline bool AreCollisionsEnabled() const { return active; }

	inline void SetIsTrigger(bool isTrigger) { IsTrigger = isTrigger; }
	inline bool GetIsTrigger() const { return IsTrigger; }

	inline const sf::FloatRect& GetHitbox() const { return rect; }

	void OnCollisionCallback(ColliderComponent* otherCollider);

private:
	bool active;
	bool IsTrigger;
	sf::FloatRect rect;
	sf::Vector2f offset;

#ifdef _USE_IMGUI
	bool displayColliderDebug;
#endif
};