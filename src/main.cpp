#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "object.h"
#include "shader.h"
#include "camera.h"
#include "Shapes.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//Globals

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const bool WIREFRAME_MODE = false;
const bool DEPTH_TESTING = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Camera
Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));
float lastMouseX = SCR_WIDTH / 2.0f;
float lastMouseY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

int main()
{
	//**************************** GLFW INIT & CONTEXT ************************************
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//glfw window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//glad loading
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//**************************** GLFW INIT & CONTEXT************************************

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	//**************************** DATA CREATION *****************************************

	glm::vec3 lightPos(1.f);
	glm::vec3 cubePos(4.f, 5.0f, 0.0f);

	glm::mat4 lightModel(1.0f), cubeModel(1.0f), sphereModel(1.f);

	lightModel = glm::scale(lightModel, glm::vec3(0.5f));

	cubeModel = glm::scale(cubeModel, glm::vec3(0.5f));
	cubeModel = glm::translate(cubeModel, cubePos);
	glm::mat4 normalCube = glm::transpose(glm::inverse(cubeModel));

	glm::mat4 normalSphere = glm::transpose(glm::inverse(sphereModel));

	//Creating Shaders
	Shader baseVertex("shaders/base.vs", "shaders/base.fs", ShaderType::BaseST);
	Shader planetSP("shaders/textured.vs", "shaders/textured.fs", ShaderType::TextureST);

	std::vector<const char*> path = { "textures/8k_earth_daymap.jpg", "textures/8k_earth_specular_map.png" };
	//Creating Textures
	Texture earth(path);
	Texture orange("textures/orange.jpg");

	//Creating Materials
	Material whiteMaterial(&baseVertex, nullptr), planetMaterial(&planetSP, &earth), orangeMaterial(&planetSP, &orange);
	whiteMaterial.AddUniform("Color", glm::vec3(1.0f, 1.0f, 1.0f));

	orangeMaterial.AddUniform("normalMat", normalCube);
	//orangeMaterial.AddUniform("texture1", 0);
	orangeMaterial.AddUniform("light.ambient", glm::vec3(1.f, 1.f, 1.f));
	orangeMaterial.AddUniform("light.diffuse", glm::vec3(1.f, 1.f, 1.f));
	orangeMaterial.AddUniform("light.specular", glm::vec3(0.5f, 0.5, 0.5f));
	//orangeMaterial.AddUniform("material.diffuse", glm::vec3(0.07568f, 0.61424f, 0.07568f));
	orangeMaterial.AddUniform("material.specular", glm::vec3(0.633f, 0.727811f, 0.633f));
	orangeMaterial.AddUniform("material.shininess", 0.6f * 128.f);
	
	planetMaterial.AddUniform("normalMat", normalSphere);
	planetMaterial.AddUniform("light.ambient", glm::vec3(0.2f, 0.2f, 0.2));
	planetMaterial.AddUniform("light.diffuse", glm::vec3(1.f, 1.f, 1.f));
	planetMaterial.AddUniform("light.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	planetMaterial.AddUniform("material.diffuse", 0);
	planetMaterial.AddUniform("material.ambient", glm::vec3(0.f, 0.2f, 0.2f));
	planetMaterial.AddUniform("material.specular", 1);
	planetMaterial.AddUniform("material.shininess", 0.25f * 128.f);

	//Object
	Object worldGrid = Shapes::genWorldGrid(&whiteMaterial, 50, 20.f);
	Object lightSource = Shapes::genSimpleCube(&whiteMaterial);
	Object diffuseCube = Shapes::genCube(&orangeMaterial);
	Object sphere = Shapes::genUVSphere(&planetMaterial, 20, 20, 1.0f);

	diffuseCube.SetModel(cubeModel);
	sphere.SetModel(sphereModel);

	//wireframe mode
	if (WIREFRAME_MODE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (DEPTH_TESTING)
		glEnable(GL_DEPTH_TEST);
	//This enables Vsync
	glfwSwapInterval(1);


	glm::mat4 projection;
	projection = glm::perspective(glm::radians(camera.Fov), static_cast<float>(SCR_WIDTH) / SCR_HEIGHT, 0.1f, 1000.0f);

	//**************************** RENDER *****************************************

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// ImGui
		/*
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
		*/

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glm::mat4 view = camera.GetViewMatrix();


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//**************************** DRAWING *****************************************

		lightPos = glm::vec3(sin(glfwGetTime() * 2) * 8, 0, cos(glfwGetTime() * 2) * 8);
		glm::mat4 lightModel2 = glm::translate(lightModel, lightPos);
		lightSource.SetModel(lightModel2);

		
		orangeMaterial.AddUniform("light.position", lightPos);
		planetMaterial.AddUniform("light.position", lightPos);
		orangeMaterial.AddUniform("viewPos", camera.Position);
		planetMaterial.AddUniform("viewPos", camera.Position);

		worldGrid.Activate(view, projection);
		worldGrid.Draw();

		lightSource.Activate(view, projection);
		lightSource.Draw();

		diffuseCube.Activate(view, projection);
		diffuseCube.Draw();

		sphere.Activate(view, projection);
		sphere.Draw();
		
		// ImGui Rendering
		/*
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		*/

		glfwSwapBuffers(window);
	}

	//object.Clean();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessDirectionInput(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessDirectionInput(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessDirectionInput(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessDirectionInput(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessDirectionInput(DOWNWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessDirectionInput(UPWARD, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

	camera.ProcessRotationInput(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessScrollInput(yoffset);
}