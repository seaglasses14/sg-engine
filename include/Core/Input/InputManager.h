#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>

struct InputState
{
	// Mouse Input

	double lastMouseX = 0;
	double lastMouseY = 0;
	double deltaX = 0;
	double deltaY = 0;
	bool firstMouse = true;

	// Mouse Scroll
	double scrollOffsetY = 0;

	// Key Presses

	bool keys[GLFW_KEY_LAST] = {};
	bool keys_prev[GLFW_KEY_LAST] = {};
};

class InputManager
{
public:
	InputManager();

	static InputManager& Get();
	InputState& GetInputState();

	bool IsKeyDown();

	float GetMouseDeltaX();
	float GetMouseDeltaY();
	
	bool cameraMode = false;
	bool viewportHovered = false;

private:
	InputState state;
};