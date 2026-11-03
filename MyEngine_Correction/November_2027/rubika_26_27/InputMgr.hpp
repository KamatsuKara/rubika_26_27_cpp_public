#pragma once

#include <DebugMgr.h>
#include <unordered_map>

#include "InputAction.h"

#include <filesystem>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

class InputMgr : public IDebugable {
public:

	void Init();
	void Start();
	void Update(float deltaTime);
	void Shut();

	virtual void DrawDebug() override;

	void CreateInputAction(std::string inputActionName);
	void RemoveInputAction(std::string inputActionName);

	void RegisterToInputAction(std::string inputActionName, const std::string& debugName, std::function<void(float)> callback, void* owner);
	void UnregisterToInputAction(std::string inputActionName, void* owner);

	void BindAction(sf::Keyboard::Key key, std::string inputActionName);

	bool LoadInput(const std::filesystem::path&);

	static std::string KeyToString(sf::Keyboard::Key);
	static sf::Keyboard::Key StringToKey(std::string);

private:
	struct sInputBind {
		sf::Keyboard::Key key;
		std::vector<std::size_t> inputActions;
	};

	std::unordered_map<std::size_t, InputAction> InputActions;
	std::vector<sInputBind> InputBinds;
};