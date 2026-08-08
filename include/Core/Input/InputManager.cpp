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
	state.deltaX_prev = state.deltaX;
	state.deltaY_prev = state.deltaY;
	state.deltaX = 0.0f;
	state.deltaY = 0.0f;
}

void InputManager::OnKeyCallback(int key, int action)
{
	OnGenericKeyCallback(state.keys, DEVICE_OFFSET_KEYBOARD, key, action);
}

void InputManager::OnMouseKeyCallback(int key, int action)
{
	OnGenericKeyCallback(state.mouse_keys, DEVICE_OFFSET_MOUSE, key, action);
}

void InputManager::OnGenericKeyCallback(bool* key_states, int device_offset, int key, int action)
{
	if(action == GLFW_PRESS || action == GLFW_RELEASE)
		key_states[key] = action;
	
	int code = ToInputCode(key, device_offset);
	if(!inputMapping.bindings.contains(code))
		return;

	for(InputAction* ia : inputMapping.bindings.at(code))
	{
		bool wasActive = !ia->activeBindings.empty();

		if(key_states[key])
			ia->activeBindings.insert(code);
		else
			ia->activeBindings.erase(code);

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

void InputManager::OnMouseCallback(double xpos, double ypos)
{
	if(state.firstMouse)
	{
		state.lastMouseX = xpos;
		state.lastMouseY = ypos;
		state.firstMouse = false;
		//return;
	}
	state.deltaX = xpos - state.lastMouseX;
	state.deltaY = state.lastMouseY - ypos; // reversed since y range from bottom to top
	state.lastMouseX = xpos;
	state.lastMouseY = ypos;


	if(!inputMapping.bindings.contains(Mouse_Delta))
		return;
	for(InputAction* ia : inputMapping.bindings.at(Mouse_Delta))
	{
		eventQueue.emplace(ia->id, InputTrigger::Pressed, glm::vec2(state.deltaX, state.deltaY));
	}
}

void InputManager::OnScrollCallback(double yoffset)
{
	state.scrollOffsetY = yoffset;

	for(InputAction* ia : inputMapping.bindings[Mouse_Scroll])
	{
		eventQueue.emplace(ia->id, InputTrigger::Pressed, static_cast<float>(yoffset));
	}
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

bool InputManager::IsMouseKeyDown(int glfw_key)
{
    if(glfw_key < GLFW_MOUSE_BUTTON_LAST)
    	return state.mouse_keys[glfw_key];
	return false;
}

bool InputManager::IsMouseKeyUp(int glfw_key)
{
    if(glfw_key < GLFW_MOUSE_BUTTON_LAST)
    	return !state.mouse_keys[glfw_key];
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

glm::vec2 InputManager::GetMousePosition()
{
    return { state.lastMouseX, state.lastMouseY };
}

bool InputManager::BindListener(std::string actionId, InputTrigger trigger, std::function<void(const ActionValue&)> listenerFunction)
{
	listeners[actionId][trigger].push_back(listenerFunction);
    return false;
}

void InputManager::ProcessEvents()
{
	if(mode != SceneViewer)
		return;
	
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
	std::memcpy(state.mouse_keys_prev, state.mouse_keys, sizeof(state.mouse_keys));
}
