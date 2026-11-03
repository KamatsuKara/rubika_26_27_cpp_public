#pragma once

#include "DebugMgr.h"

#include <functional>
#include <string>
#include <vector>

class InputAction : public IDebugable
{
public:
	InputAction() = default;
	InputAction(const std::string& name);
	void SetActionName(const std::string& name);
	inline std::string GetActionName() { return ActionName; }
	void SetValue(float value);
	void RegisterCallback(const std::string& debugName, std::function<void(float)> callback, void* owner);
	void UnregisterCallbacks(void* owner);

	virtual void DrawDebug() override;

private:
	struct sCallbackInfo
	{
		std::string DebugName;
		std::function<void(float)> Callback;
		void* Owner = nullptr;
	};

	std::string ActionName;
	std::size_t ActionNameHash;
	float Value = 0.f;
	std::vector<sCallbackInfo> Callbacks;
};