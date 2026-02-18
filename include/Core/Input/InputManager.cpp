#include "Core/Input/InputManager.h"

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
