#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <queue>
#include <string>
#include "Core/Input/InputAction.h"
#include "Core/Input/InputMapping.h"

enum InputMode
{
	Editor,
	SceneViewer,
	Game
};

enum InputTrigger
{
	Started, 	//First frame pressed
	Pressed, 	//All frames pressed including Started frame
	Finished	//First frame released
};

struct InputState
{
	// Mouse Input

	double lastMouseX = 0;
	double lastMouseY = 0;
	double deltaX = 0;
	double deltaY = 0;
	double deltaX_prev = 0;
	double deltaY_prev = 0;
	bool firstMouse = true;

	// Mouse Scroll
	double scrollOffsetY = 0;

	// Key Presses

	bool keys[GLFW_KEY_LAST + 1] = { };
	bool keys_prev[GLFW_KEY_LAST + 1] = {};

	bool mouse_keys[GLFW_MOUSE_BUTTON_LAST + 1] = {};
	bool mouse_keys_prev[GLFW_MOUSE_BUTTON_LAST + 1] = {};
};

struct InputEvent
{
	InputEvent(std::string id, InputTrigger trigger, ActionValue value)
        : id(std::move(id)), trigger(trigger), value(std::move(value))
    {}

	std::string id;
	InputTrigger trigger;
	ActionValue value;
};

class InputManager
{
public:
	InputManager();

	static InputManager& Get();
	InputState& GetInputState();

	void RefreshPerFrameValue();

	// Adding events in queue
	void OnKeyCallback(int key, int action);
	void OnMouseKeyCallback(int key, int action);
	void OnMouseCallback(double xpos, double ypos);
	void OnScrollCallback(double yoffset);

	bool IsKeyDown(int glfw_key);
	bool IsKeyUp(int glfw_key);

	bool IsMouseKeyDown(int glfw_key);
	bool IsMouseKeyUp(int glfw_key);

	float GetMouseDeltaX();
	float GetMouseDeltaY();

	glm::vec2 GetMousePosition();

	InputMapping inputMapping;
	std::vector<InputAction*> inputActions;

	bool BindListener(std::string actionId, InputTrigger trigger, std::function<void(const ActionValue&)> listenerFunction );

	void ProcessEvents();

	InputMode mode = InputMode::Editor;
	bool viewportHovered = false;

private:
	InputState state;

	std::unordered_map<InputAction*, InputEvent> activeActions;
	std::queue<InputEvent> eventQueue;
	
	std::unordered_map<
		std::string,
		std::unordered_map<
			InputTrigger,
			std::vector<std::function<void(const ActionValue&)>
			>
		>
	> listeners;

	void OnGenericKeyCallback(bool* key_states, int device_offset ,int key, int action);
};