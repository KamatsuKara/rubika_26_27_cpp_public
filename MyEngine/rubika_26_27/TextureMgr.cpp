#include "TextureMgr.h"

#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <iostream>

#include "Globals.h"
#include "Logger.h"

bool readXmlAnimations(rapidxml::xml_node<char>*, TextureData&, std::string);
bool readXmlAnimationData(rapidxml::xml_node<char>*, AnimationData&, std::string, std::string);
bool readXmlBackgrounds(rapidxml::xml_node<char>*, TextureData&, std::string);
bool readXmlStaticTileData(rapidxml::xml_node<char>*, StaticTileData&, std::string, std::string);


TextureData::TextureData(Type type):type(type) {

}

TextureData::~TextureData() {

}

void TextureMgr::Init()
{
	gData.DebugMgr->RegisterDebugableWindow("Textures", this);
}

void TextureMgr::Shut()
{
	gData.DebugMgr->UnregisterDebugableWindow("Textures");
}

bool TextureMgr::LoadTexture(const std::filesystem::path& path) {
	std::filesystem::path xmlPath = path;
	xmlPath.replace_extension(".xml");

	if (!std::filesystem::exists(path)) {
		Logger::Error("LoadTexture failed : no texture file (" + path.string() +")"); return false;
	}
	if (!std::filesystem::exists(xmlPath)) {
		Logger::Error("LoadTexture failed : no metadata file (" + xmlPath.string() + ")"); return false;
	}

	std::string fileName = path.stem().string();
	
	rapidxml::xml_document<> metadata;
	rapidxml::file<> xmlFile(xmlPath.string().c_str());
	try {
		metadata.parse<0>(xmlFile.data());
	}
	catch(const char* msg){
		Logger::Error("LoadTexture failed ("+ fileName +") : fail to parse metadata file(" + std::string(msg) + ")"); return false;
	}

	rapidxml::xml_node<char>* root = metadata.first_node();
	if (root == nullptr) {
		Logger::Error("LoadTexture failed (" + fileName + ") : no first node in xml file"); return false;
	}

	TextureData texture = TextureData(TextureData::Type::Animation);
	if (strcmp(root->name(), "Animations") == 0) {
		if (!readXmlAnimations(root, texture, fileName)) return false;
	}
	else if (strcmp(root->name(), "Backgrounds") == 0) {
		TextureData texture = TextureData(TextureData::Type::StaticTile);
		if (!readXmlBackgrounds(root, texture, fileName)) return false;
	}
	else {
		Logger::Error("LoadTexture failed (" + fileName + ") : first node unrecognized"); return false;
	}

	if (!texture.Texture.loadFromFile(path)) {
		Logger::Error("LoadTexture failed (" + fileName + ") : fail to load image"); return false;
	}
	textures.insert({ fileName, texture });

	return true;
}

const TextureData& TextureMgr::GetTextureData(const std::string& name) const {
	const auto& texture = textures.find(name);
	if (texture != textures.end()) return texture->second;
	else return TextureData(TextureData::Type::Animation);
}

void TextureMgr::DrawDebug()
{
#ifdef _USE_IMGUI

#endif
}


bool readXmlAnimations(rapidxml::xml_node<char>* root, TextureData& texture, std::string fileName) {
	rapidxml::xml_node<char>* anim = root->first_node("Animation");
	while (anim != nullptr) {
		if (anim->first_attribute("Name") == nullptr) {
			Logger::Error("LoadTexture failed (" + fileName + ") : a animation doesn't have a name"); return false; }
		std::string animName = anim->first_attribute("Name")->value();

		if (texture.animationData.find(animName) == texture.animationData.end()) {
			AnimationData animData = AnimationData();
			if (!readXmlAnimationData(anim, animData, fileName, animName)) return false;
			texture.animationData.insert({ animName, animData });
		}
		else {
			Logger::Error("LoadTexture failed (" + fileName + ") : a animation already have the name : " + animName); return false; }

		anim = anim->next_sibling();
	}
	return true;
}
bool readXmlAnimationData(rapidxml::xml_node<char>* anim, AnimationData& animData, std::string fileName, std::string animName) {
	rapidxml::xml_node<char>* animParams = anim->first_node();
	int paramNmb = 9;
	while (animParams != nullptr) {
		if (strcmp(animParams->name(),"X") == 0) {
			paramNmb--;
			try { animData.StartX = std::stoi(animParams->value()); }
			catch(const char* msg){
				Logger::Error("LoadTexture failed (" + fileName + "."+ animName +") : invalide value for X"); return false;
			}
		}
		else if (strcmp(animParams->name(),"Y") == 0) {
			paramNmb--;
			try { animData.StartY = std::stoi(animParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + animName + ") : invalide value for Y"); return false;
			}
		}
		else if (strcmp(animParams->name(),"SizeX") == 0) {
			paramNmb--;
			try { animData.SizeX = std::stoi(animParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + animName + ") : invalide value for SizeX"); return false;
			}
		}
		else if (strcmp(animParams->name(),"SizeY") == 0) {
			paramNmb--;
			try { animData.SizeY = std::stoi(animParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + animName + ") : invalide value for SizeY"); return false;
			}
		}
		else if (strcmp(animParams->name(),"OffsetX") == 0) {
			paramNmb--;
			try { animData.OffsetX = std::stoi(animParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + animName + ") : invalide value for OffsetX"); return false;
			}
		}
		else if (strcmp(animParams->name(),"OffsetY") == 0) {
			paramNmb--;
			try { animData.OffsetY = std::stoi(animParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + animName + ") : invalide value for OffsetY"); return false;
			}
		}
		else if (strcmp(animParams->name(),"SpriteNum") == 0) {
			paramNmb--;
			try { animData.AnimationSpriteCount = std::stoi(animParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + animName + ") : invalide value for SpriteNum"); return false;
			}
		}
		else if (strcmp(animParams->name(),"SpritesOnLine") == 0) {
			paramNmb--;
			try { animData.SpriteOnLine = std::stoi(animParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + animName + ") : invalide value for SpritesOnLine"); return false;
			}
		}
		else if (strcmp(animParams->name(),"Reverted") == 0) {
			paramNmb--;
			try { animData.IsReverted = std::stoi(animParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + animName + ") : invalide value for Reverted"); return false;
			}
		}
		animParams = animParams->next_sibling();
	}
	if(paramNmb != 0){
		Logger::Error("LoadTexture failed (" + fileName + "." + animName + ") : invalide count of params " + std::to_string(paramNmb)); return false;
	}
	return true;
}

bool readXmlBackgrounds(rapidxml::xml_node<char>* root, TextureData& texture, std::string fileName) {
	rapidxml::xml_node<char>* tile = root->first_node("Animation");
	while (tile != nullptr) {
		if (tile->first_attribute("Name") == nullptr) {
			Logger::Error("LoadTexture failed (" + fileName + ") : a tile doesn't have a name"); return false;
		}
		std::string tileName = tile->first_attribute("Name")->value();

		if (texture.animationData.find(tileName) == texture.animationData.end()) {
			StaticTileData tileData = StaticTileData();
			if (!readXmlStaticTileData(tile, tileData, fileName, tileName)) return false;
			texture.staticTileData.insert({ tileName, tileData });
		}
		else {
			Logger::Error("LoadTexture failed (" + fileName + ") : a tile already have the name : " + tileName); return false;
		}

		tile = tile->next_sibling();
	}
	return true;
}
bool readXmlStaticTileData(rapidxml::xml_node<char>* tile, StaticTileData& tileData, std::string fileName, std::string tileName) {
	rapidxml::xml_node<char>* tileParams = tile->first_node();
	int paramNmb = 6;
	while (tileParams != nullptr) {
		if (strcmp(tileParams->name(),"X") == 0) {
			paramNmb--;
			try { tileData.StartX = std::stoi(tileParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + tileName + ") : invalide value for X"); return false;
			}
		}
		else if (strcmp(tileParams->name(),"Y") == 0) {
			paramNmb--;
			try { tileData.StartY = std::stoi(tileParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + tileName + ") : invalide value for Y"); return false;
			}
		}
		else if (strcmp(tileParams->name(),"SizeX") == 0) {
			paramNmb--;
			try { tileData.SizeX = std::stoi(tileParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + tileName + ") : invalide value for SizeX"); return false;
			}
		}
		else if (strcmp(tileParams->name(),"SizeY") == 0) {
			paramNmb--;
			try { tileData.SizeY = std::stoi(tileParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + tileName + ") : invalide value for SizeY"); return false;
			}
		}
		else if (strcmp(tileParams->name(),"RevertedX") == 0) {
			paramNmb--;
			try { tileData.IsRevertedX = std::stoi(tileParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + tileName + ") : invalide value for RevertedX"); return false;
			}
		}
		else if (strcmp(tileParams->name(),"RevertedY") == 0) {
			paramNmb--;
			try { tileData.IsRevertedY = std::stoi(tileParams->value()); }
			catch (const char* msg) {
				Logger::Error("LoadTexture failed (" + fileName + "." + tileName + ") : invalide value for RevertedY"); return false;
			}
		}
		
		tileParams = tileParams->next_sibling();
	}
	if (paramNmb != 0) {
		Logger::Error("LoadTexture failed (" + fileName + "." + tileName + ") : invalide count of params"); return false;
	}
	return true;

}