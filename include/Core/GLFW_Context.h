#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLFW_Context
{
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 800;
	const bool WIREFRAME_MODE = false;
	const bool DEPTH_TESTING = true;

public:
	GLFW_Context();
	bool IsRunning();
	void AtEndOfLoop();
	GLFWwindow* GetWindow();

private:
	unsigned int GLFW_CONTEXT_STATE = 0;
	GLFWwindow* window;
};

