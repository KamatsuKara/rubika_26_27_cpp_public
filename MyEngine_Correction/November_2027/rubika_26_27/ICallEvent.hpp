#pragma once

#include <string>
#include <vector>

template <typename F>
class ICallEvent
{
public:
	void RegisterCallback(const std::string& debugName, F callback, void* owner);
	void UnregisterCallbacks(void* owner);

protected:
	struct sCallbackInfo
	{
		std::string DebugName;
		F Callback;
		void* Owner = nullptr;
	};

	std::vector<sCallbackInfo> Callbacks;
};

template <typename F>
void ICallEvent<F>::UnregisterCallbacks(void* owner) {
	for (std::size_t i = 0; i < Callbacks.size(); i++)
	{
		if (Callbacks[i].Owner == owner) {
			Callbacks.erase(Callbacks.begin() + i);
			i--;
		}
	}
}

template <typename F>
void ICallEvent<F>::RegisterCallback(const std::string& debugName, F callback, void* owner){
	Callbacks.push_back({ debugName,callback,owner });
}