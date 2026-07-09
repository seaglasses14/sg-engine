#include "Core/Input/InputManager.h"
#include "InputManager.h"

InputManager::InputManager() {}

InputManager& InputManager::Get()
{
	static InputManager instance;
	return instance;
}

InputState& InputManager::GetInputState()
{
	return state;
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
