#include "InputAction.h"

#include <Imgui/imgui.h>

InputAction::InputAction(const std::string& name):ActionName(name),ActionNameHash(std::hash<std::string>{}(ActionName)) {

}

void InputAction::SetActionName(const std::string& name) {
	ActionName = name;
	ActionNameHash = std::hash<std::string>{}(ActionName);
}

void InputAction::SetValue(float value) {
	if (Value == value) return;

	Value = value;
	for (auto callback : Callbacks)
	{
		callback.Callback(Value);
	}
}

void InputAction::DrawDebug()
{
#ifdef _USE_IMGUI
	bool bTree = ImGui::TreeNode(ActionName.c_str());
	if (bTree)
	{
		for (sCallbackInfo callbackInfo : Callbacks) {
			ImGui::Text(callbackInfo.DebugName.c_str());
		}
		ImGui::TreePop();
	}
#endif
}
