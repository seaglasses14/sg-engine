#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene/Scene.h"

class GLFW_Context
{
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 800;
	const bool WIREFRAME_MODE = true;
	const bool DEPTH_TESTING = true;
	float lastMouseX = SCR_WIDTH / 2.0f;
	float lastMouseY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

public:
	GLFW_Context();
	bool IsRunning();
	void AtEndOfLoop();
	GLFWwindow* GetWindow();
	Scene* scene = nullptr;

private:
	unsigned int GLFW_CONTEXT_STATE = 0;
	GLFWwindow* window;

	static void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height);
	static void mouse_callback(GLFWwindow* pWindow, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* pWindow, double xoffset, double yoffset);
	static void key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods);

	void instanced_framebuffer_size_callback(GLFWwindow* pWindow, int width, int height);
	void instanced_mouse_callback(GLFWwindow* pWindow, double xpos, double ypos);
	void instanced_scroll_callback(GLFWwindow* pWindow, double xoffset, double yoffset);
	void instanced_key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
};

