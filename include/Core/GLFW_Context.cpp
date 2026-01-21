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
	
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	

	// GLFW Callbacks

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Glad Loading
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Log::Error("Failed to initialize GLAD");
		glfwTerminate();
		GLFW_CONTEXT_STATE = 1;
	}
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//wireframe mode
	if (WIREFRAME_MODE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (DEPTH_TESTING)
		glEnable(GL_DEPTH_TEST);
	//This enables Vsync
	glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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

void GLFW_Context::framebuffer_size_callback(GLFWwindow* pWindow, int width, int height)
{
	GLFW_Context* instance = static_cast<GLFW_Context*>(glfwGetWindowUserPointer(pWindow));
	instance->instanced_framebuffer_size_callback(pWindow, width, height);
}

void GLFW_Context::mouse_callback(GLFWwindow* pWindow, double xpos, double ypos)
{
	GLFW_Context* instance = static_cast<GLFW_Context*>(glfwGetWindowUserPointer(pWindow));
	instance->instanced_mouse_callback(pWindow, xpos, ypos);
}

void GLFW_Context::scroll_callback(GLFWwindow* pWindow, double xoffset, double yoffset)
{
	GLFW_Context* instance = static_cast<GLFW_Context*>(glfwGetWindowUserPointer(pWindow));
	instance->instanced_scroll_callback(pWindow, xoffset, yoffset);
}

void GLFW_Context::instanced_framebuffer_size_callback(GLFWwindow* pWindow, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GLFW_Context::instanced_mouse_callback(GLFWwindow* pWindow, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastMouseX = xpos;
		lastMouseY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastMouseX;
	float yoffset = lastMouseY - ypos; // reversed since y range from bottom to top
	lastMouseX = xpos;
	lastMouseY = ypos;

	if(scene == nullptr)
		Log::Warning("GLFW_Context::instanced_mouse_callback(): scene is nullptr");
	else
		scene->mainCamera->ProcessRotationInput(xoffset, yoffset);
}

void GLFW_Context::instanced_scroll_callback(GLFWwindow* pWindow, double xoffset, double yoffset)
{
	if (scene == nullptr)
		Log::Warning("GLFW_Context::instanced_scroll_callback(): scene is nullptr");
	else
		scene->mainCamera->ProcessScrollInput(yoffset);
}
