#include "Obstacle.hpp"

#include "Globals.h"

#include "TransformComponent.h"
#include "MovementComponent.hpp"
#include "ColliderComponent.h"
#include "RenderComponent.h"

#include "InputMgr.hpp"

#include <RectangleDrawable.h>

Obstacle::Obstacle(std::string friendlyName) :Entity(friendlyName) {
    TransformComponent* tc = AddComponent<TransformComponent>();
    {
        tc->SetWorldPosition(sf::Vector2f(100.f, 100.f));
    }

    ColliderComponent* cc = AddComponent<ColliderComponent>();
    {
        cc->SetHitboxSize(sf::Vector2f(50, 50));
        cc->SetHitboxOffset(sf::Vector2f(0, 0));
    }

    RenderComponent* rc = AddComponent<RenderComponent>();
    {
        RectangleDrawable* tile = rc->AddNewDrawable<RectangleDrawable>("tile", sf::Vector2f(0, 0), 0, sf::Vector2f(1, 1));
        tile->SetVisibility(true);
        tile->SetTexture("../Ressources/Basement.png");
        tile->SetTile("Corner_Top_Left");
    }
}

Obstacle::~Obstacle() {

}