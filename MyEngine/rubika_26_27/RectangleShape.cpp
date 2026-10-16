#include "RectangleShape.hpp"
#include "Globals.h"
#include "Logger.h"

#include <SFML/Graphics/RectangleShape.hpp>

RectangleShape::RectangleShape() {
	Drawable = new sf::RectangleShape(sf::Vector2f(50,50));
	WorldTransform = sf::Transform();
}

void RectangleShape::setFillColor(sf::Color color) {
	sf::RectangleShape* shape = static_cast<sf::RectangleShape*>(Drawable);
	shape->setFillColor(color);
}

void RectangleShape::Start()
{
	if (staticTileData != nullptr) {
		sf::RectangleShape* shape = static_cast<sf::RectangleShape*>(Drawable);
		sf::IntRect rect(
			sf::Vector2i(staticTileData->StartX, staticTileData->StartY),
			sf::Vector2i(staticTileData->SizeX, staticTileData->SizeY));
		shape->setTexture(&textureData->Texture);
		shape->setTextureRect(rect);
	}
}

void RectangleShape::Update(float fDeltaTime)
{
}

void RectangleShape::Destroy()
{
}

bool RectangleShape::SetTexture(const std::string& textureName) {
	textureData = &gData.TextureMgr->GetTextureData(textureName);
	if(textureData->GetType() == TextureData::Type::StaticTile)
		return true;
	else {
		Logger::Error("Wrong type of texture in a Rectangle Shape"); return false;
	}
}

bool RectangleShape::SetStaticTile(const std::string& staticTileName) {
	if (textureData == nullptr) {
		Logger::Error("Try to set a Tile in a Rectangle Shape but no texture is set"); return false;
	}
	if (textureData->staticTileData.find(staticTileName) != textureData->staticTileData.end())
		staticTileData = &textureData->staticTileData.find(staticTileName)->second;
	else {
		Logger::Error("Try to set a Tile in a Rectangle Shape but no texture tile name " + staticTileName); return false;
	}
	return true;
}

bool RectangleShape::SetTextureAndStaticTile(const std::string& textureName, const std::string& staticTileName) {
	return SetTexture(textureName) && SetStaticTile(staticTileName);
}