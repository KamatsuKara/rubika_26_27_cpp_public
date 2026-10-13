#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif

#include "Globals.h"

#include "SceneMgr.hpp"
#include "Logger.h"


SceneMgr::SceneMgr() {
	scenes = {};
	activeScene = nullptr;
}

void SceneMgr::Init()
{
	gData.DebugMgr->RegisterDebugableWindow("Scenes", this);
}

void SceneMgr::Shut()
{
	gData.DebugMgr->UnregisterDebugableWindow("Scenes");
}

SceneMgr::~SceneMgr() {
}

void SceneMgr::Start() {
	if (activeScene == nullptr) {
		Logger::Warning("There no active scene (SceneMgr::Start)");
		return;
	}
	activeScene->Start();
}

void SceneMgr::Update(float fDeltaTime) {
	if (activeScene == nullptr) {
		Logger::Warning("There no active scene (SceneMgr::Update)");
		return;
	}
	activeScene->Update(fDeltaTime);
}

void SceneMgr::Destroy() {
	if (activeScene == nullptr) {
		Logger::Warning("There no active scene (SceneMgr::Destroy)");
		return;
	}
	activeScene->Destroy();
}

Scene* SceneMgr::AddScene(std::string sceneName) {
	if (!scenes.contains(sceneName)) {
		scenes.insert({ sceneName, Scene(sceneName)});
		return &scenes.find(sceneName)->second;
	}
	else {
		Logger::Error("A scene has already the name " + sceneName + " (SceneMgr::AddScene)");
		return nullptr;
	}
}

bool SceneMgr::SetActiveScene(std::string& sceneName) {
	if (scenes.contains(sceneName)) {
		activeScene = &scenes.find(sceneName)->second;
		return true;
	}
	else {
		Logger::Error("There is no scene name " + sceneName + " (SceneMgr::SetActiveScene)");
		return false;
	}
}

void SceneMgr::DrawDebug()
{
#ifdef _USE_IMGUI

	//for (const std::pair<std::string, Scene>& scenePair : scenes) {
	for (const auto& scenePair : scenes) {
		std::string sceneName = scenePair.second.GetName();
		ImGui::PushID(sceneName.c_str());
		bool isOpen = ImGui::TreeNode("");
		ImGui::SameLine();
		if (activeScene != nullptr && scenePair.second.GetName() == activeScene->GetName()) {
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), sceneName.c_str(), sceneName);
		}
		else {
			ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), sceneName.c_str(), sceneName);
			ImGui::SameLine();
			if (ImGui::Button("Set Active"))
			{
				SetActiveScene(sceneName);
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Add Entity"))
		{
			Scene& scene = const_cast<Scene&>(scenePair.second);
			scene.AddEntity("Entity" + std::to_string(scenePair.second.GetNmbEntity()));
		}

		if (isOpen)
		{			
			for (int i = 0; i < scenePair.second.GetNmbEntity(); i++) {
				ImGui::Text(scenePair.second.GetEntity(i)->GetFriendlyName().c_str());
			}
			ImGui::TreePop();
		}
		ImGui::PopID();
	}
#endif
}
