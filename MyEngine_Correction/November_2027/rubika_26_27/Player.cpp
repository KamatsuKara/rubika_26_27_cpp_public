#include "Player.hpp"

#include "Globals.h"

#include "TransformComponent.h"
#include "MovementComponent.hpp"
#include "ColliderComponent.h"
#include "PhysicComponent.hpp"
#include "RenderComponent.h"

#include "InputMgr.hpp"

#include <SpriteDrawable.h>

Player::Player(std::string friendlyName) :Entity(friendlyName) {
    TransformComponent* tc = AddComponent<TransformComponent>();
    {
        tc->SetWorldPosition(sf::Vector2f(100.f, 100.f));
    }

    MovementComponent* mc = AddComponent<MovementComponent>();
    {
        mc->SetSpeed(30);
    }

    ColliderComponent* cc = AddComponent<ColliderComponent>();
    {
        cc->SetHitboxSize(sf::Vector2f(25, 30));
        cc->SetHitboxOffset(sf::Vector2f(0, -18));
    }

    PhysicComponent* pc = AddComponent<PhysicComponent>();
    {

    }

    RenderComponent* rc = AddComponent<RenderComponent>();
    {
        SpriteDrawable* bodySprite = rc->AddNewDrawable<SpriteDrawable>("Body", sf::Vector2f(2, 0), 0, sf::Vector2f(1, 1));
        bodySprite->SetVisibility(true);
        bodySprite->SetTexture("../Ressources/IsaacSprite.png");
        bodySprite->SetAnimation("Body_Vertical");

        SpriteDrawable* headSprite = rc->AddNewDrawable<SpriteDrawable>("Head", sf::Vector2f(-2.5f, -20), 0, sf::Vector2f(1, 1));
        headSprite->SetVisibility(true);
        headSprite->SetTexture("../Ressources/IsaacSprite.png");
        headSprite->SetAnimation("Head_Down");
    }

    gData.InputMgr->RegisterToInputAction(
        "Up", "Up",
        [this](float v) {
            this->GetComponent<MovementComponent>()->SetDirection(
                sf::Vector2f(this->GetComponent<MovementComponent>()->GetDirection().x, v == 1 ? -1 : 0));
        },
        this);
    gData.InputMgr->RegisterToInputAction(
        "Down", "Down",
        [this](float v) {
            this->GetComponent<MovementComponent>()->SetDirection(
                sf::Vector2f(this->GetComponent<MovementComponent>()->GetDirection().x, v == 1 ? 1 : 0));
        },
        this);
    gData.InputMgr->RegisterToInputAction(
        "Right", "Right",
        [this](float v) {
            this->GetComponent<MovementComponent>()->SetDirection(
                sf::Vector2f(v == 1 ? 1 : 0, this->GetComponent<MovementComponent>()->GetDirection().y));
        },
        this);
    gData.InputMgr->RegisterToInputAction(
        "Left", "Left",
        [this](float v) {
            this->GetComponent<MovementComponent>()->SetDirection(
                sf::Vector2f(v == 1 ? -1 : 0, this->GetComponent<MovementComponent>()->GetDirection().y));
        },
        this);
}

Player::~Player() {

}