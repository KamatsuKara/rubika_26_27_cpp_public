#pragma once

#include "DebugMgr.h"
#include "ICallEvent.hpp"

#include <functional>
#include <string>
#include <vector>

class InputAction : public IDebugable, public ICallEvent< std::function<void(float)>>
{
public:
	InputAction() = default;
	InputAction(const std::string& name);
	void SetActionName(const std::string& name);
	inline std::string GetActionName() { return ActionName; }
	void SetValue(float value);

	virtual void DrawDebug() override;

private:
	std::string ActionName;
	std::size_t ActionNameHash;
	float Value = 0.f;
};