#include "Sprite.hpp"
#include "Globals.h"
#include "Logger.h"

#include <SFML/Graphics/Sprite.hpp>

Sprite::Sprite(const sf::Texture& texture) {
	sprite = new sf::Sprite(texture);
	Drawable = sprite;
}


void Sprite::Start()
{
	animationStep = 0;
	sf::IntRect rect(
		sf::Vector2i(animationData->StartX, animationData->StartY),
		sf::Vector2i(animationData->SizeX, animationData->SizeY));
	sprite->setTexture(textureData->Texture);
	sprite->setTextureRect(rect);

}

void Sprite::Update(float fDeltaTime)
{
	static float timer = 0;
	timer += fDeltaTime;
	if (timer > animationData->TimeBetweenAnimationInS * 1000.f) {
		timer = 0;
		animationStep++;
		if (animationStep >= animationData->SpriteOnLine)
			animationStep = 0;
	}

	sf::IntRect rect(
		sf::Vector2i(
			animationData->StartX + (animationData->OffsetX * animationStep),
			animationData->StartY + (animationData->OffsetY * animationStep)),
		sf::Vector2i(animationData->SizeX,animationData->SizeY));
	sprite->setTexture(textureData->Texture);
	sprite->setTextureRect(rect);
}

void Sprite::Destroy()
{
}

bool Sprite::SetTexture(const std::string& textureName) {
	textureData = &gData.TextureMgr->GetTextureData(textureName);
	if (textureData->GetType() == TextureData::Type::Animation)
		return true;
	else {
		Logger::Error("Wrong type of texture in a Sprite"); return false;
	}
}

bool Sprite::SetAnimation(const std::string& animationName) {
	if (textureData == nullptr) {
		Logger::Error("Try to set a Animation in a Sprite but no texture is set"); return false;
	}
	if (textureData->staticTileData.find(animationName) != textureData->staticTileData.end())
		animationData = &textureData->animationData.find(animationName)->second;
	else {
		Logger::Error("Try to set Animation in a Sprite but no texture animation name " + animationName); return false;
	}
	return true;
}

bool Sprite::SetTextureAndAnimation(const std::string& textureName, const std::string& animationName) {
	return SetTexture(textureName) && SetAnimation(animationName);
}