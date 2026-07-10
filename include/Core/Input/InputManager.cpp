#include "InputManager.h"
#include <cstring>

InputManager::InputManager()
{
}

InputManager& InputManager::Get()
{
	static InputManager instance;
	return instance;
}

InputState& InputManager::GetInputState()
{
	return state;
}

void InputManager::RefreshPerFrameValue()
{
	state.deltaX = 0.0f;
	state.deltaY = 0.0f;
}

void InputManager::OnKeyCallback(int key, int action)
{
	if(action == GLFW_PRESS || action == GLFW_RELEASE)
		state.keys[key] = action;

	for(InputAction* ia : inputMapping.bindings[key])
	{
		bool wasActive = !ia->activeBindings.empty();

		if(state.keys[key])
			ia->activeBindings.insert(key);
		else
			ia->activeBindings.erase(key);

		bool isActive = !ia->activeBindings.empty();

		if(!wasActive && isActive)
		{
			activeActions.try_emplace(ia, ia->id, InputTrigger::Pressed, true);
			eventQueue.emplace(ia->id, InputTrigger::Started, true);
		}
		if(wasActive && !isActive)
		{
			activeActions.erase(ia);
			eventQueue.emplace(ia->id, InputTrigger::Finished, false);
		}
	}
}

void InputManager::OnMouseCallback()
{
}

void InputManager::OnScrollCallback()
{
}

bool InputManager::IsKeyDown(int glfw_key)
{
	// Add better error management
	if(glfw_key < GLFW_KEY_LAST)
    	return state.keys[glfw_key];
	return false;
}

bool InputManager::IsKeyUp(int glfw_key)
{
    if(glfw_key < GLFW_KEY_LAST)
    	return !state.keys[glfw_key];
	return false;
}

float InputManager::GetMouseDeltaX()
{
    return state.deltaX;
}

float InputManager::GetMouseDeltaY()
{
    return state.deltaY;
}

bool InputManager::BindListener(std::string actionId, InputTrigger trigger, std::function<void(const ActionValue&)> listenerFunction)
{
	listeners[actionId][trigger].push_back(listenerFunction);
    return false;
}

void InputManager::ProcessEvents()
{
	// Continuous events creation must be changed
	// Triggered Events
	for(auto& [ia, event] : activeActions)
	{
		eventQueue.emplace(event);
	}

	// Process events
	while(!eventQueue.empty())
	{
		InputEvent e = std::move(eventQueue.front());

		eventQueue.pop();

		for(const auto& listener : listeners[e.id][e.trigger])
		{
			listener(e.value);
		}
	}

	// Update previous values
	std::memcpy(state.keys_prev, state.keys, sizeof(state.keys));
}
