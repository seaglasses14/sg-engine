#include "GLFW_Context.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Log.h"

GLFW_Context::GLFW_Context()
{
	Log::Info("Initializing GLFW context: 3.3 Core");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	Log::Info("Window Hint for Apple System");
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// GLFW Window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SG_Engine", NULL, NULL);
	if (window == NULL)
	{
		Log::Error("Failed to create GLFW window");
		glfwTerminate();
		GLFW_CONTEXT_STATE = 1;
	}
	Log::Info("Successfully created window");

	// GLFW Callbacks
	glfwMakeContextCurrent(window);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);

	// Glad Loading
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Log::Error("Failed to initialize GLAD");
		glfwTerminate();
		GLFW_CONTEXT_STATE = 1;
	}
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

bool GLFW_Context::IsRunning()
{
	return !glfwWindowShouldClose(window);
}

// Must be called at the end of the main loop
void GLFW_Context::AtEndOfLoop()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
	if (GLFW_CONTEXT_STATE > 0)
	{
		glfwSetWindowShouldClose(window, true);
		Log::Error("Program will terminate ||| CONTEXT_STATE = " + GLFW_CONTEXT_STATE);
	}
		

}
GLFWwindow* GLFW_Context::GetWindow()
{
	if (window != nullptr)
		return window;
	GLFW_CONTEXT_STATE = 1;
	Log::Error("GLFW_Context::GetWindow(): window is nullptr");
	return nullptr;
}
