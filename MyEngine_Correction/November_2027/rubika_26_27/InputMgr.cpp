#include "InputMgr.hpp"

#include <Globals.h>
#include "Logger.h"

#include <Imgui/imgui.h>
#include <rapidxml/rapidxml_utils.hpp>

void InputMgr::Init()
{
	gData.DebugMgr->RegisterDebugableWindow("InputMgr", this);
}

void InputMgr::Start()
{

}

void InputMgr::Update(float deltaTime)
{
	for (sInputBind& inputBind : InputBinds) {
		for (std::size_t inputActionHash : inputBind.inputActions) {
			auto inputAction = InputActions.find(inputActionHash);
			if (inputAction != InputActions.end())
				inputAction->second.SetValue(sf::Keyboard::isKeyPressed(inputBind.key) ? 1.0f : -1.0f);
			else
				gData.Logger->Error("InputMgr : A key is bind to a InputAction that doesn't exist");
		}
	}
}

void InputMgr::Shut()
{
	gData.DebugMgr->UnregisterDebugableWindow("InputMgr");
}


void InputMgr::CreateInputAction(std::string inputActionName) {
	std::size_t inputActionHash = std::hash<std::string>{}(inputActionName);

	if (!InputActions.contains(inputActionHash))
		InputActions.insert({ inputActionHash, InputAction(inputActionName)});
	else
		gData.Logger->Warning("InputMgr : Try to create a InputAction that already exist");
}

void InputMgr::RemoveInputAction(std::string inputActionName) {
	std::size_t inputActionHash = std::hash<std::string>{}(inputActionName);
	auto inputAction = InputActions.find(inputActionHash);
	
	if (inputAction != InputActions.end())
		InputActions.erase(inputAction);
	else
		gData.Logger->Warning("InputMgr : Try to remove a InputAction that doesn't exist");

	for (sInputBind& inputBind : InputBinds) {
		auto it = std::find(inputBind.inputActions.begin(), inputBind.inputActions.end(), inputActionHash);
		if (it != inputBind.inputActions.end())
			inputBind.inputActions.erase(it);
	}
}


void InputMgr::RegisterToInputAction(std::string inputActionName, const std::string& debugName, std::function<void(float)> callback, void* owner) {
	std::size_t inputActionHash = std::hash<std::string>{}(inputActionName);
	auto inputAction = InputActions.find(inputActionHash);

	if (inputAction == InputActions.end()) {
		gData.Logger->Error("InputMgr : Try to register to a InputAction that doesn't exist");
		return;
	}

	inputAction->second.RegisterCallback(debugName, callback, owner);
}

void InputMgr::UnregisterToInputAction(std::string inputActionName, void* owner) {
	std::size_t inputActionHash = std::hash<std::string>{}(inputActionName);
	auto inputAction = InputActions.find(inputActionHash);

	if (inputAction == InputActions.end()) {
		gData.Logger->Error("InputMgr : Try to unregister to a InputAction that doesn't exist");
		return;
	}

	inputAction->second.UnregisterCallbacks(owner);
}


void InputMgr::BindAction(sf::Keyboard::Key key, std::string inputActionName) {
	std::size_t inputActionHash = std::hash<std::string>{}(inputActionName);

	if (!InputActions.contains(inputActionHash)) {
		gData.Logger->Error("InputMgr : Try to bind a InputAction that doesn't exist (" + inputActionName + ")");
		return;
	}

	for (sInputBind& inputBind : InputBinds) {
		if (inputBind.key == key) {
			inputBind.inputActions.push_back(inputActionHash);
			return;
		}
	}
	InputBinds.push_back({ key,{inputActionHash} });
}

bool InputMgr::LoadInput(const std::filesystem::path& path) {
	if (!std::filesystem::exists(path.native()))
	{
		std::cerr << "Input file doesn't exist " << path << std::endl;
		return false;
	}

	rapidxml::file<> inputFile(path.string().c_str());
	if (inputFile.size() == 0)
	{
		std::cerr << "Cannot open Input file " << path << std::endl;
		return false;
	}

	rapidxml::xml_document inputXml;
	inputXml.parse<0>(inputFile.data());

	if (rapidxml::xml_node<>* inputActions = inputXml.first_node("InputActions")) {
		rapidxml::xml_node<>* inputAction = inputActions->first_node("InputAction");
		while (inputAction) {
			CreateInputAction(inputAction->first_attribute("Name")->value());
			inputAction = inputAction->next_sibling("InputAction");
		}
	}
	else return false;

	if (rapidxml::xml_node<>* bindings = inputXml.first_node("Bindings")) {
		rapidxml::xml_node<>* binding = bindings->first_node("Binding");
		while (binding) {
			rapidxml::xml_node<>* input = binding->first_node();
			if (strcmp(input->name(), "Keyboard") == 0) {
				sf::Keyboard::Key key = StringToKey(input->first_attribute("Key")->value());

				rapidxml::xml_node<>* action = binding->first_node("InputAction");
				while (action) {
					BindAction(key, action->value());
					action = action->next_sibling("InputAction");
				}
			}
			binding = binding->next_sibling("Binding");
		}
	}else return false;

	return true;
}


void InputMgr::DrawDebug()
{
#ifdef _USE_IMGUI
	ImGui::SeparatorText("InputActions :");
	for (std::pair<std::size_t, InputAction> inputActionPair : InputActions) {
		inputActionPair.second.DrawDebug();
	}
	ImGui::SeparatorText("Bindings :");
	for (sInputBind inputBind : InputBinds) {
		bool bTree = ImGui::TreeNode(InputMgr::KeyToString(inputBind.key).c_str());
		if (bTree)
		{
			for (std::size_t inputActionHash : inputBind.inputActions) {
				auto inputAction = InputActions.find(inputActionHash);
				ImGui::Text(inputAction->second.GetActionName().c_str());
			}
			ImGui::TreePop();
		}
	}
#endif
}

std::string InputMgr::KeyToString(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Key::A) return "A";
	else if (key == sf::Keyboard::Key::B) return "B";
	else if (key == sf::Keyboard::Key::C) return "C";
	else if (key == sf::Keyboard::Key::D) return "D";
	else if (key == sf::Keyboard::Key::E) return "E";
	else if (key == sf::Keyboard::Key::F) return "F";
	else if (key == sf::Keyboard::Key::G) return "G";
	else if (key == sf::Keyboard::Key::H) return "H";
	else if (key == sf::Keyboard::Key::I) return "I";
	else if (key == sf::Keyboard::Key::J) return "J";
	else if (key == sf::Keyboard::Key::K) return "K";
	else if (key == sf::Keyboard::Key::L) return "L";
	else if (key == sf::Keyboard::Key::M) return "M";
	else if (key == sf::Keyboard::Key::N) return "N";
	else if (key == sf::Keyboard::Key::O) return "O";
	else if (key == sf::Keyboard::Key::P) return "P";
	else if (key == sf::Keyboard::Key::Q) return "Q";
	else if (key == sf::Keyboard::Key::R) return "R";
	else if (key == sf::Keyboard::Key::S) return "S";
	else if (key == sf::Keyboard::Key::T) return "T";
	else if (key == sf::Keyboard::Key::U) return "U";
	else if (key == sf::Keyboard::Key::V) return "V";
	else if (key == sf::Keyboard::Key::W) return "W";
	else if (key == sf::Keyboard::Key::X) return "X";
	else if (key == sf::Keyboard::Key::Y) return "Y";
	else if (key == sf::Keyboard::Key::Z) return "Z";
	else if (key == sf::Keyboard::Key::Space) return "Space";
	else if (key == sf::Keyboard::Key::Up) return "UpArrow";
	else if (key == sf::Keyboard::Key::Right) return "RightArrow";
	else if (key == sf::Keyboard::Key::Down) return "DownArrow";
	else if (key == sf::Keyboard::Key::Left) return "LeftArrow";
	else if (key == sf::Keyboard::Key::Tab) return "Tab";
	else if (key == sf::Keyboard::Key::LShift) return "LeftShift";
	else if (key == sf::Keyboard::Key::LControl) return "LeftControl";
	
	gData.Logger->Error("Key not found");
	return "";
}

sf::Keyboard::Key InputMgr::StringToKey(std::string keyName) {
	if (keyName == "A") return sf::Keyboard::Key::A;
	else if (keyName == "B") return sf::Keyboard::Key::B;
	else if (keyName == "C") return sf::Keyboard::Key::C;
	else if (keyName == "D") return sf::Keyboard::Key::D;
	else if (keyName == "E") return sf::Keyboard::Key::E;
	else if (keyName == "F") return sf::Keyboard::Key::F;
	else if (keyName == "G") return sf::Keyboard::Key::G;
	else if (keyName == "H") return sf::Keyboard::Key::H;
	else if (keyName == "I") return sf::Keyboard::Key::I;
	else if (keyName == "J") return sf::Keyboard::Key::J;
	else if (keyName == "K") return sf::Keyboard::Key::K;
	else if (keyName == "L") return sf::Keyboard::Key::L;
	else if (keyName == "M") return sf::Keyboard::Key::M;
	else if (keyName == "N") return sf::Keyboard::Key::N;
	else if (keyName == "O") return sf::Keyboard::Key::O;
	else if (keyName == "P") return sf::Keyboard::Key::P;
	else if (keyName == "Q") return sf::Keyboard::Key::Q;
	else if (keyName == "R") return sf::Keyboard::Key::R;
	else if (keyName == "S") return sf::Keyboard::Key::S;
	else if (keyName == "T") return sf::Keyboard::Key::T;
	else if (keyName == "U") return sf::Keyboard::Key::U;
	else if (keyName == "V") return sf::Keyboard::Key::V;
	else if (keyName == "W") return sf::Keyboard::Key::W;
	else if (keyName == "X") return sf::Keyboard::Key::X;
	else if (keyName == "Y") return sf::Keyboard::Key::Y;
	else if (keyName == "Z") return sf::Keyboard::Key::Z;
	else if (keyName == "Space") return sf::Keyboard::Key::Space;
	else if (keyName == "UpArrow") return sf::Keyboard::Key::Up;
	else if (keyName == "RightArrow") return sf::Keyboard::Key::Right;
	else if (keyName == "DownArrow") return sf::Keyboard::Key::Down;
	else if (keyName == "LeftArrow") return sf::Keyboard::Key::Left;
	else if (keyName == "Tab") return sf::Keyboard::Key::Tab;
	else if (keyName == "LeftShift") return sf::Keyboard::Key::LShift;
	else if (keyName == "LeftControl") return sf::Keyboard::Key::LControl;
	
	gData.Logger->Error("KeyName not found");
	return sf::Keyboard::Key::Space;
}