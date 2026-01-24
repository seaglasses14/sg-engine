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

#include "Scene/Scene.h"
#include "object.h"
#include "shader.h"
#include "camera.h"
#include "Shapes.h"
#include <Core/GLFW_Context.h>
#include "Core/GUI/GUI.h"

void processInput(GLFWwindow* window);

//Globals

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const bool WIREFRAME_MODE = false;
const bool DEPTH_TESTING = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Camera
Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));

int main()
{
	Scene* scene = new Scene();
	scene->mainCamera = &camera;
	
	GLFW_Context* GLFWcontext = new GLFW_Context();
	GLFWcontext->scene = scene;
	GLFWcontext->GetWindow();
	
	GUI* gui = new GUI(GLFWcontext->GetWindow());

	//**************************** DATA CREATION *****************************************

	glm::vec3 lightPos(1.f);
	glm::vec3 lightColor(1.f);

	glm::mat4 lightModel(1.0f), sphereModel(1.f);

	lightModel = glm::scale(lightModel, glm::vec3(0.5f));

	//Creating Shaders
	Shader baseVertex("shaders/base.vert", "shaders/base.frag", ShaderType::BaseST);
	Shader planetSP("shaders/textured.vert", "shaders/textured.frag", ShaderType::TextureST);

	std::vector<const char*> path = { "textures/8k_earth_daymap.jpg", "textures/matrix.jpg" ,"textures/8k_earth_clouds.jpg", "textures/8k_earth_specular_map.png" };
	std::vector<const char*> path2 = { "textures/orange.jpg", "textures/matrix.jpg" };
	
	//Creating Textures
	Texture earth(path);

	//Creating Materials
	Material whiteMaterial(&baseVertex, nullptr), planetMaterial(&planetSP, &earth);
	whiteMaterial.AddUniform("Color", lightColor);

	planetMaterial.AddUniform("light.color", lightColor);
	planetMaterial.AddUniform("material.diffuse1", 0);
	planetMaterial.AddUniform("material.diffuse2", 1);
	planetMaterial.AddUniform("material.diffuse3", 2);
	planetMaterial.AddUniform("material.ambient", glm::vec3(0.f, 0.2f, 0.2f));
	planetMaterial.AddUniform("material.specular", 3);
	planetMaterial.AddUniform("material.shininess", 0.25f * 128.f);

	//Object
	Object worldGrid = Shapes::genWorldGrid(&whiteMaterial, 50, 20.f);
	Object lightSource = Shapes::genSimpleCube(&whiteMaterial);
	Object sphere = Shapes::genUVSphere(&planetMaterial, 40, 40, 1.0f);

	sphere.SetModel(sphereModel);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(camera.Fov), static_cast<float>(SCR_WIDTH) / SCR_HEIGHT, 0.1f, 1000.0f);


	bool showDemoWindow = true;
	bool showWindow = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.f);
	//**************************** RENDER *****************************************

	while (GLFWcontext->IsRunning())
	{
		// ImGui
		glfwPollEvents();

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		if (glfwGetWindowAttrib(GLFWcontext->GetWindow(), GLFW_ICONIFIED))
		{
			ImGui_ImplGlfw_Sleep(10);
			continue;
		}

		gui->StartDrawing();

		//Demo Window
		if(showDemoWindow)
			ImGui::ShowDemoWindow(&showDemoWindow);
		static float f = 0.0f;
		static int counter = 0;

		/*
		ImGui::Begin("First Window");
		ImGui::Text("Mammt");
		ImGui::Checkbox("Show Demo", &showDemoWindow);
		ImGui::Checkbox("Show Other Window", &showWindow);
		ImGui::SliderFloat("float", &f, 0.f, 1.f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
		ImGui::ColorEdit3("ClearColor", (float*)&clear_color);

		if(ImGui::Button("Button"))
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);
		
		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.f / io.Framerate, io.Framerate);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000 * deltaTime, 1 / deltaTime);
		ImGui::End();

		if (showWindow)
		{
			ImGui::Begin("Window", &showWindow);
			ImGui::Text("New Window");
			if (ImGui::Button("Close"))
				showWindow = false;
			ImGui::End();
		}

		*/

		gui->Draw();

		processInput(GLFWcontext->GetWindow());

		glm::mat4 view = camera.GetViewMatrix();


		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//**************************** DRAWING *****************************************

		//lightPos = glm::vec3(sin(glfwGetTime()) * 8, 0, cos(glfwGetTime()) * 8);
		lightPos = glm::vec3(0, 0, -10 + 5 * sin(glfwGetTime()));
		
		glm::mat4 lightModel2 = glm::translate(lightModel, lightPos);
		lightSource.SetModel(lightModel2);

		glm::mat4 normalSphere = glm::transpose(glm::inverse(view * sphereModel));

		planetMaterial.AddUniform("normalMat", normalSphere);
		planetMaterial.AddUniform("lightPos", lightPos);
		planetMaterial.AddUniform("light.constant", 1.0f);
		planetMaterial.AddUniform("light.linear", 0.02f);
		planetMaterial.AddUniform("light.quadratic", 0.007f);
		planetMaterial.AddUniform("directLight.direction", glm::vec3(view * glm::normalize(glm::vec4(-0.2f, -1.0f, -0.3f, 0))));
		planetMaterial.AddUniform("light.position", lightPos);
		planetMaterial.AddUniform("viewPos", camera.Position);

		worldGrid.Activate(view, projection);
		worldGrid.Draw();

		lightSource.Activate(view, projection);
		lightSource.Draw();


		sphere.Activate(view, projection);
		sphere.Draw();
		
		// ImGui Rendering
		
		gui->Render();

		GLFWcontext->AtEndOfLoop();
	}

	//object.Clean();

	gui->Shutdown();

	glfwDestroyWindow(GLFWcontext->GetWindow());
	glfwTerminate();

	return 0;
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